CC							:= gcc
OBJDUMP					:= objdump
MKMMIMG					:= ../../eric/eric_tools/mkmmimg

INCLUDE_DIR			:= -Isources/include/

ARCH := $(shell uname -m | sed s,i[3456789]86,ia32,)

INCLUDES 				:=	$(INCLUDE_DIR)

LIB_GCC	 				:= $(shell $(CC) -print-libgcc-file-name)
LIBS 						:= # $(LIB_GCC)

CRT_OBJS		 		:= build/crt0/crt0.o
LDS 						:= linker.ld

CC_FLAGS_ALL		:= -Wall -Werror -Werror -O2 -fno-stack-protector \
		-fno-strict-aliasing -fshort-wchar $(INCLUDES) -fno-builtin -fPIC -O0

LD_FLAGS_ALL		:= -nostdlib -T $(LDS) -shared -Bsymbolic \
		$(CRT_OBJS) -znocombreloc -fPIC --no-undefined

define SRC_2_OBJ
  $(foreach src,$(1),$(patsubst sources/%,build/%,$(src)))
endef

define SRC_2_BIN
  $(foreach src,$(1),$(patsubst sources/%,binary/%,$(src)))
endef

define SRC_2_BUILD
  $(foreach src,$(1),$(patsubst sources/%,build/%,$(src)))
endef

all: targets
# make -C test

# Overriden in rules.mk
TARGETS :=
OBJECTS :=

dir	:= sources
include	$(dir)/rules.mk

build/%.o: sources/%.s
	@echo "  [CC]    $< -> $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS_ALL) $(CC_FLAGS_TARGET) -o $@ -c $<

build/%.o: sources/%.c
	@echo "  [CC]    $< -> $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS_ALL) $(CC_FLAGS_TARGET) -o $@ -c $<

binary/%.bin: binary/%.bin.raw
	@echo "  [CRC]   $< -> $@"
	@$(MKMMIMG) $< write $@

binary/%.bin.raw: binary/%.elf
	@echo "  [OC]    $< -> $@"
	@# @strip $@
	@objcopy -O binary -j .text -j .sdata -j .data $(OBJCPY_FLAGS_TARGET) $< $@

binary/%.elf: build/crt0/crt0.o
	@echo "  [LD]    $@"
	@mkdir -p $(dir $@)
	@$(LD) $(LD_FLAGS_ALL) $(LD_FLAGS_TARGET) $(LD_OBJECTS) -o $@ $(LIBS)

targets: $(patsubst sources/%, binary/%, $(TARGETS)) build/crt0/crt0.o

clean:
	@rm -f $(TARGETS) $(OBJECTS)

info:
	@echo Targets [$(TARGETS)]
	@echo Objects [$(OBJECTS)]

copy: $(TARGETS)
	@echo "  [CP]"
	@echo $(TARGETS) | grep bin$ | awk '{print " -v "$$1" \
		../../eric/tftpy/root/"}' | xargs cp

# Disassemble raw 64 bit binary
# objdump -D binary/cpuid/cpuid.bin -b binary -m i386:x86-64
