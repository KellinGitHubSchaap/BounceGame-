#ifndef GBA_PALETTE_DEF_H
#define GBA_PALETTE_DEF_H

// === Summary ===
/// There are 6 tile-blocks (CHARBLOCKS), that is 4 for backgrounds (0-3) and 2 for sprites (4-5).
/// Each charblock is 16kb of memory (4000h bytes) long.

#include "gba_type_def.h"

typedef u16 PALBANK4[16];	//!<  When using a palette with bits per pixel set to 4
typedef u16 PALBANK8[256];	//!<  When using a palette with bits per pixel set to 8

#define REG_OBJ_PAL	((u16*) 0x05000200) //!< Palette register for objects

#define REG_OBJ_PAL4 ((PALBANK4*) REG_OBJ_PAL)	//!< If a sprite consists out of tiles that are 4bpp
#define REG_OBJ_PAL8 ((PALBANK8*) REG_OBJ_PAL)	//!< If a sprite consists out of tiles that are 8bpp

#endif // !GBA_PALETTE_DEF_H
