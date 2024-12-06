CC = clang -target armv7-none-eabihf
AR = llvm-ar
OBJCOPY = llvm-objcopy

CFLAGS = -Wall -Wextra -Wpedantic
LDFLAGS = -fuse-ld=lld
OPTFLAGS = -O0 -g

SRCS = $(wildcard src/*/*.c)
ASMS = $(wildcard src/*/*.S)
OBJS = $(SRCS:.c=.o) $(ASMS:.S=.o)

ifndef VERBOSE
V := @
endif

all: build/kernel.img

release: OPTFLAGS = -O3
release: build/kernel.img

build/kernel.elf: $(OBJS) src/link.ld
	@printf " \033[1;34mLD\033[0m kernel.elf\n"
	$(V)$(CC) -nostdlib -T src/link.ld $(OBJS) -lclang_rt.builtins -o $@ $(LDFLAGS) $(OPTFLAGS)

build/kernel.img: build/kernel.elf
	@printf " \033[1;35mOC\033[0m kernel.img\n"
	$(V)$(OBJCOPY) -O binary $< $@

%.o: %.c $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -Iinclude -D__UNIQLIBC_PRIVATE_API -ffreestanding -fpic -std=c99 $(CFLAGS) $(OPTFLAGS) -c $< -o $@

$(ASMS:.S=.o): %.o: %.S $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) -Iinclude -D__UNIQLIBC_PRIVATE_API $(ASFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf build/* src/*/*.o

run: build/kernel.elf
	@printf "Running with QEMU...\n"
	$(V)qemu-system-aarch64 -M raspi2b -kernel $< -serial stdio

debug: build/kernel.elf
	@printf "Running with QEMU in debug mode...\n"
	$(V)qemu-system-aarch64 -M raspi2b -kernel $< -serial stdio -s -S

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, -D__UNIQLIBC_PRIVATE_API, --target=armv7-none-eabihf, -ffreestanding]\n' > .clangd

.PHONY: all clean run debug
