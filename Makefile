# SHELL = /bin/sh
# .SUFFIXES:
# .SUFFIXES: .c .o .h .lex


REQUIRES :=
CC := gcc
CFLAGS := -std=c11 -I./include -I./build -D_POSIX_C_SOURCE=199309L -D_GNU_SOURCE
LDLIBS :=
LDFLAGS :=
PROGRAM := test

empty :=
ifneq ($(REQUIRES),$(empty))
CFLAGS += `pkg-config --cflags $(REQUIRES)`
LDLIBS += `pkg-config --libs-only-l $(REQUIRES)`
LDFLAGS += `pkg-config --libs-only-L --libs-only-other $(REQUIRES)`
endif


get-stem = $(notdir $(basename $(1)))
get-object-rule = build/$(shell $(CC) -I./include -MM -MG $(1) | sed 's/\\//g')


c-source-list := $(wildcard src/*.c)
c-object-rules = $(foreach c-src, $(c-source-list), $(eval $(call get-object-rule, $(c-src))))
c-stems := $(call get-stem, $(c-source-list))
c-object-list := $(addprefix build/, $(addsuffix .o, $(c-stems)))


build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@




LEX := flex
LFLAGS :=

build/%.c: src/%.lex
	$(LEX) $(LFLAGS) -o $@ $<
	cp $@ ./tmp

build/%.o: build/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#-------------------------------------------------------------------------------------
$(PROGRAM): $(c-object-list)
	$(CC) $(CFLAGS) $(LDFLAGS) $(c-object-list) -o $(PROGRAM) $(LDLIBS)


$(c-object-rules)




#-------------------------------------------------------------------------------------
.PHONY: clean debug
clean:
	rm -f build/*.o tmp/* $(PROGRAM)

debug:
	@echo $(c-source-list)
