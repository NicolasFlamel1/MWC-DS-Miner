# Check if devkitPro is installed
ifneq ($(DEVKITARM),)

# Build with devkitPro
include $(DEVKITARM)/ds_rules
CFLAGS = -specs="ds_arm9.specs"
LIBS = -lfilesystem -lfat
NDSTOOL = "$(DEVKITARM)/../tools/bin/ndstool"

# Otherwise check if BlocksDS is installed
else ifneq ($(BLOCKSDS),)

# Build with BlocksDS
CXX = $(BLOCKSDS)/../../../toolchain/gcc-arm-none-eabi/bin/arm-none-eabi-g++
LIBNDS = $(BLOCKSDS)/libs/libnds
CFLAGS = -specs="$(BLOCKSDS)/sys/crts/ds_arm9.specs" -I "$(BLOCKSDS)/libs/dswifi/include" -Diprintf=printf -Dsiprintf=sprintf
LIBS = -L "$(BLOCKSDS)/libs/dswifi/lib" -lc
NDSTOOL = "$(BLOCKSDS)/tools/ndstool/ndstool"

# Otherwise
else

# Display error
$(error devkitPro or BlocksDS is required)

endif

# Program parameters
NAME = "MWC_DS_Miner"
CFLAGS += -I "$(LIBNDS)/include" -DARM9 -mthumb -mcpu=arm946e-s+nofp -Ofast -Wall -Wextra -Wno-missing-field-initializers -Wno-ignored-qualifiers -Wno-unused-but-set-variable -std=c++20 -finput-charset=UTF-8 -fexec-charset=UTF-8 -funsigned-char -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti
LIBS += -L "$(LIBNDS)/lib" -ldswifi9 -lnds9
SRCS = "./main.cpp" "./ram.c"
EMULATOR = "./melonDS"
PROGRAM_NAME = $(subst $\",,$(NAME))

# Make
make:
	"$(CXX)" $(CFLAGS) -o "./$(PROGRAM_NAME).elf" $(SRCS) $(LIBS)
	$(NDSTOOL) -c "./$(PROGRAM_NAME).nds" -9 "./$(PROGRAM_NAME).elf" -b "./icon.bmp" "$(subst $\_, ,$(PROGRAM_NAME))" -d "./nitrofs"

# Clean
clean:
	rm -f "./$(PROGRAM_NAME).elf" "./$(PROGRAM_NAME).nds" "./$(PROGRAM_NAME)"

# Run
run:
	$(EMULATOR) "./$(PROGRAM_NAME).nds"

# Icon
icon:
	"convert" -define bmp:format=bmp3 -type Palette -colors 16 -compress none -dither FloydSteinberg "./icon.png" "./icon.bmp"

# Linux
linux:
	"g++" -std=c++20 -o "./$(PROGRAM_NAME)" "./main.cpp"

# Run Linux
runLinux:
	"./$(PROGRAM_NAME)"
