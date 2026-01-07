CC = clang -target arm-none-eabihf -mcpu=cortex-a7
AR = llvm-ar
OBJCOPY = llvm-objcopy

COMPILER_RT_VERSION := 21.1.8

CFLAGS = -Wall -Wextra -pedantic
OPTFLAGS = -O0 -g

SRCS = $(wildcard src/*/*.c) compiler-rt/lib/builtins/udivmoddi4.c
ASMS = $(wildcard src/*/*.S) compiler-rt/lib/builtins/arm/aeabi_uldivmod.S
OBJS = $(SRCS:.c=.o) $(ASMS:.S=.o)

ifndef VERBOSE
V := @
endif

all: build/kernel.img

release: OPTFLAGS = -O2
release: build/kernel.img

build/kernel.elf: $(OBJS) src/link.ld
	@printf " \033[1;34mLD\033[0m kernel.elf\n"
	$(V)$(CC) -nostdlib -T src/link.ld $(OBJS) -o $@ $(LDFLAGS) $(OPTFLAGS)

build/kernel.img: build/kernel.elf
	@printf " \033[1;35mOC\033[0m kernel.img\n"
	$(V)$(OBJCOPY) -O binary $< $@

%.o: %.c $(HEADERS) compiler-rt
	@src=$@; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -Iinclude -D__UNIQLIBC_PRIVATE_API -ffreestanding -fpic -std=c99 $(CFLAGS) $(OPTFLAGS) -c $< -o $@

$(ASMS:.S=.o): %.o: %.S $(HEADERS) compiler-rt
	@src=$@; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) -Iinclude -D__UNIQLIBC_PRIVATE_API $(ASFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf build/* src/*/*.o

distclean: clean
	$(V)rm -rf compiler-rt .clangd

compiler-rt:
	@printf "Downloading compiler-rt...\n"
	$(V)rm -rf compiler-rt
	$(V)curl -# -L https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPILER_RT_VERSION)/compiler-rt-$(COMPILER_RT_VERSION).src.tar.xz | xz -d | tar -x
	$(V)mv compiler-rt-$(COMPILER_RT_VERSION).src compiler-rt

run: build/kernel.elf
	@printf "Running with QEMU...\n"
	$(V)qemu-system-arm -M raspi2b -kernel $< -serial stdio

debug: build/kernel.elf
	@printf "Running with QEMU in debug mode...\n"
	$(V)qemu-system-arm -M raspi2b -kernel $< -serial stdio -s -S

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, -D__UNIQLIBC_PRIVATE_API, --target=armv7-none-eabihf, -ffreestanding]\n' > .clangd

.PHONY: all clean run debug
