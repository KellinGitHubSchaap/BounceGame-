#ifndef GBA_BASE_DEF_H
#define GBA_BASE_DEF_H

#include "gba_type_def.h"

#define EWRAM		0x02000000	//!< This space is available for game data and code. If a multiboot cable is present on startup, the BIOS automatically detects it and downloads binary code from the cable and places it in this area, and execution begins with the instruction address. Memory transfer to and from EWRAM are 16-bits wide and is slower.
#define IWRAM		0x03000000	//!< This space is the fastest of all GBA RAM, and is 32 bit wide. Placing the ARM code in here is better.
#define REG_BASE	0x04000000	//!< This area of memory is used for the control of graphics, sound, DMA, and other features.
#define MEM_PAL		0x05000000	//!< Memory area where palettes are stored
#define SRAM		0x0E000000	//!< Used primarily to save data
#define VRAM		0x06000000	//!< The Video RAM is used to store the framebuffer of bitmapped modes, and tile data and tilemaps for tile-based "text"and scaling/rotating modes

#endif // !GBA_BASE_DEF_H

