# Daedalus Firmware

This directory contains the firmware for the RP2350 board.

## Building

### Using the Makefile (Recommended)

The project includes a Makefile that simplifies the build process:

1. Make sure you have the Pico SDK set up (automatically handled by the Nix flake)
2. Build the firmware:
   ```
   make
   ```
3. The output files will be in the `build` directory

### Manual Build

If you prefer to use CMake directly:

1. Configure the build:
   ```
   cmake -B build -S .
   ```
2. Build the firmware:
   ```
   cmake --build build
   ```
3. The output files will be in the `build` directory:
   - `daedalus_firmware.uf2`: UF2 file for drag-and-drop programming
   - `daedalus_firmware.elf`: ELF file for debugging
   - `daedalus_firmware.hex`: HEX file for programming with external tools

## Flashing

### Using the Makefile (Recommended)

Flash the firmware to the RP2350 board:

```
make flash
```

If the board is already running firmware and needs to be forced into programming mode:

```
make FORCE_FLASH=1 flash
```

### Manual Flashing

Connect the RP2350 board in bootloader mode (hold BOOTSEL while connecting USB) and copy the UF2 file:

```
cp build/daedalus_firmware.uf2 /path/to/rp2350/
```

Or use picotool:

```
picotool load -x build/daedalus_firmware.uf2
```

## Debugging

Generate disassembly for debugging:

```
make disasm
```

## Development

The firmware uses both cores of the RP2040:
- Core 0: Handles the main application logic
- Core 1: Manages the LED matrix display

The LED matrix is organized in a 4x6 grid, with rows and columns controlled by GPIO pins.