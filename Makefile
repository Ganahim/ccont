
REQUIRES :=
CC := gcc
CFLAGS := -std=c11 -I./include
LDLIBS :=
LDFLAGS :=
PROGRAM := test
empty :=

ifneq ($(REQUIRES),$(empty))
CFLAGS += `pkg-config --cflags $(REQUIRES)`
LDLIBS += `pkg-config --libs-only-l $(REQUIRES)`
LDFLAGS += `pkg-config --libs-only-L --libs-only-other $(REQUIRES)`
endif


c-source-list := $(wildcard src/*.c)
get-object-rule = build/$(shell $(CC) -I./include -MM -MG $(1) | sed 's/\\//g')
c-object-rules = $(foreach c-src, $(c-source-list), $(eval $(call get-object-rule, $(c-src))))

get-stem = $(notdir $(basename $(1)))
c-stems := $(call get-stem, $(c-source-list))
c-object-list := $(addprefix build/, $(addsuffix .o, $(c-stems)))


build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(PROGRAM): $(c-object-list)
	$(CC) $(CFLAGS) $(LDFLAGS) $(c-object-list) -o $(PROGRAM) $(LDLIBS)


$(c-object-rules)


.PHONY: clean debug
clean:
	rm -f build/*.o $(PROGRAM)

debug:
