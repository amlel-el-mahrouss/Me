CXX=x86_64-elf-g++

FLAGS=-Wall -Werror -mno-sse2 -mno-sse -std=c++20 -c\
    -ffreestanding \
    -nostdlib \
    -fno-exceptions \
    -fno-rtti \
    -I./ -I./MeKit -I../KernelKit -fno-builtin -D__KDBG__ -D__KERNEL__ -D__MeKernel__ -fPIC ../

HAL=$(wildcard HALKit/AMD64/*.cpp) $(wildcard HALKit/AMD64/*.s)
LD=x86_64-elf-ld
SCRIPT=--script=Other/Script.ld
TARGET=MeKernel.elf

.PHONY: KernelBuild
KernelBuild:
	$(CXX) $(FLAGS) \
    $(wildcard Source/*.cpp) \
    $(HAL)

.PHONY: Optional
Optional:
	rm -rf Temp
	mkdir Temp
	mv $(wildcard *.o) Temp


.PHONY: KernelLink
KernelLink:
	$(LD) $(wildcard *.o) $(wildcard Temp/*.o) $(SCRIPT) -o $(TARGET)

.PHONY: KernelClean
KernelClean:
	rm -f $(TARGET) && rm -rf Temp $(wildcard *.o)

ISO_IMG=MeOS.iso

.PHONY: RunAlpha
RunAlpha:
	qemu-system-alpha -smp cores=4 -m 4G -append 'console=ttys0' -kernel $(ISO_IMG) -d int

.PHONY: RunAMD64
RunAMD64:
	qemu-system-x86_64 -M q35 -smp cores=4 -m 4G -device pvpanic -cdrom $(ISO_IMG) -d int



