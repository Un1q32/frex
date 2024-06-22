CC := clang -target aarch64-elf
LD := aarch64-elf-ld
OBJCOPY := aarch64-elf-objcopy

CFLAGS := -Wall -Wextra -Wpedantic
OPTFLAGS := -g -O0 -mcpu=cortex-a72+nosimd

SRCS := $(wildcard src/*.c)
ASMS := $(wildcard src/*.S)
OBJS := $(SRCS:.c=.o) $(ASMS:.S=.o)

HEADERS := $(wildcard include/*.h) $(wildcard include/*/*.h)

ifndef VERBOSE
V := @
endif

.PHONY: all release clean clangd

all: kernel8.img

release: OPTFLAGS := -O3
release: all

kernel8.img: kernel8.elf
	@printf " \033[1;35mCP\033[0m kernel8.img\n"
	$(V)$(OBJCOPY) -O binary $< kernel8.raw
	$(V)gzip -nc kernel8.raw > kernel8.img
	$(V)rm kernel8.raw

kernel8.elf: $(OBJS) src/link.ld
	@printf " \033[1;34mLD\033[0m kernel8.elf\n"
	$(V)$(LD) -m aarch64elf -nostdlib -T src/link.ld $(LDFLAGS) -o $@ $(OBJS)

$(ASMS:.S=.o): %.o: %.S $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) -Iinclude $(OPTFLAGS) -c $< -o $@

%.o: %.c $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -ffreestanding -std=c99 -Iinclude $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf src/*.o *.elf *.img

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, --target=aarch64-elf, -std=c99]\n' > .clangd
