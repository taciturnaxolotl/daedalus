# Daedalus Firmware

This directory contains the firmware for the RP2350 board.

## Building

1. Make sure you have the Pico SDK set up (automatically handled by the Nix flake)
2. Configure the build:
   ```
   cmake -B build -S .
   ```
3. Build the firmware:
   ```
   cmake --build build
   ```
4. The output files will be in the `build` directory:
   - `daedalus_firmware.uf2`: UF2 file for drag-and-drop programming
   - `daedalus_firmware.elf`: ELF file for debugging
   - `daedalus_firmware.hex`: HEX file for programming with external tools

## Flashing

Connect the RP2350 board in bootloader mode (hold BOOTSEL while connecting USB) and copy the UF2 file:

```
cp build/daedalus_firmware.uf2 /path/to/rp2350/
```

Or use picotool:

```
picotool load -x build/daedalus_firmware.uf2
```