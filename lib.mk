
REQUIRES :=
CC := gcc
CFLAGS := -I./include
LDFLAGS := -shared
LDLIBS :=
OBJFLAGS := -c -fPIC
empty :=

ifneq ($(REQUIRES),$(empty))
CFLAGS += `pkg-config --cflags $(REQUIRES)`
LDLIBS += `pkg-config --libs-only-l $(REQUIRES)`
LDFLAGS += `pkg-config --libs-only-L --libs-only-other $(REQUIRES)`
endif


libname-base := containers
libname-shared := lib$(libname-base).so
libname-static := lib$(libname-base).a

c-source-files := $(wildcard src/*.c)
c-source-stems := $(notdir $(basename $(c-source-files)))
c-object-files := $(foreach stem, $(c-source-stems), build/$(stem).o)

c-object-rule = build/$(shell $(CC) -I./include -MM -MG $(1) | sed 's/\\//g')
c-object-rules = $(foreach src, $(c-source-files), $(eval $(call c-object-rule, $(src))))



# standard installation related variables
prefix 		:= /home/michael/media/DATA1/c-modules
exec_prefix := $(prefix)
includedir 	:= $(prefix)/include/$(libname-base)
libdir 		:= $(exec_prefix)/lib

# nonstandard
libversion	:= 0.1.0


define pkgconfig-file :=
Name: $(libname-base)
Description:
Version: $(libversion)
Cflags: -I$(includedir)
Libs: -L$(libdir) -Wl,-rpath=$(libdir) -l$(libname-base)
endef




# This is used to keep a log of which files were installed and where
log-entry = $(file >>.install_log,$(1))

# Installation functions
define install-libs =
cp lib/$(libname-shared) lib/$(libname-static) $(1)
$(call log-entry, $(1)/$(libname-shared))
$(call log-entry, $(1)/$(libname-static))
endef

define install-headers =
cp include/*.h $(1)
$(call log-entry, $(1))
endef

define install-pkgconfig-file =
$(file >$(1)/$(libname-base).pc,$(pkgconfig-file))
$(call log-entry, $(1)/$(libname-base).pc)
endef

define install-source-tarball =
tar -ca . -f $(1)/$(libname-base)-$(libversion).tar.gz
endef

define install-other =
cp .install_log $(1)/.$(libname-base)_install_log
$(call log-entry, $(1)/.$(libname-base)_install_log)
endef


# Pattern rules
build/%.o: src/%.c
	$(CC) $(CFLAGS) $(OBJFLAGS) $< -o $@

#----------------------------------------------------------------------------------------------
# Rules
all: lib/$(libname-shared) lib/$(libname-static)

lib/$(libname-shared): $(c-object-files)
	$(CC) $(CFLAGS) $(LDFLAGS) $(c-object-files) -o $@ $(LDLIBS)

lib/$(libname-static): $(c-object-files)
	ar rcs $@ $^

$(c-object-rules)




#----------------------------------------------------------------------------------------------
.PHONY: clean install uninstall purge debug

install:
	mkdir -p $(libdir) $(includedir)
	$(call install-libs, $(libdir))
	$(call install-headers, $(includedir))

	$(call install-pkgconfig-file, $(libdir)/pkgconfig)
	$(call install-source-tarball, $(prefix)/src)

	$(call install-other, $(prefix))

uninstall:
	for FILE in `cat .install_log`; do rm -r -f $$FILE; echo "removing $$FILE"; done
	rm -f .install_log

clean:
	rm -f build/*.o lib/lib*.a lib/lib*.so*

debug:
	$(file >$(libname-base).pc,$(pkgconfig-file))
