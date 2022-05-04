#ifndef GBA_TILEBLOCK_DEF_H
#define GBA_TILEBLOCK_DEF_H

#include "gba_type_def.h"

typedef struct { u32 data[8]; } TILE, TILE4;	//!< 8x8 tile using 4bpp

typedef struct { u32 data[16]; } TILE8;			//!< d-tile: double-sized tile using 8bpp

typedef TILE CHARBLOCK[512];		//!< tile block: 32x16 s-tiles
typedef TILE8 CHARBLOCK8[256];		//!< tile block: 16x16 d-tiles

#define tile_mem ((CHARBLOCK*) 0x06000000)
#define tile8_mem ((CHARBLOCK8*) 0x06000000)

#endif // !GBA_TILEBLOCK_DEF_H
