#ifndef GBA_BACKGROUND_DEF_H
#define GBA_BACKGROUND_DEF_H

#include "gba_type_def.h"
#include "gba_base_def.h"

#define ALIGN4	__attribute__((aligned(4)))

// Tilepalette = Colors used per tile
// Tileset = Tiles that were made and can be used
// Tilemap = A system which stores and transfers tile type, position, and palette 

// The tileset is stored in the Charblock the CHARBLOCK (tileblock) and the tilemap goes into the Screenblock

// Tile (or Charblock) = tileset
// Screen Entry (SE) (or Screenblock) = tilemaps

#define REG_BG0_CNT		*(vu16*)(REG_BASE + 0x0008)	//!< Control over background 0
#define BG0_HOR_OFFSET	*(vu16*)(REG_BASE + 0x0010)	//!< Horizontal offset	| Write only | CANT BE UPDATED WITH THE '+=' OR '-=' ARITHMETIC 
#define BG0_VER_OFFSET	*(vu16*)(REG_BASE + 0x0012)	//!< Vertical offset	| Write only | CANT BE UPDATED WITH THE '+=' OR '-=' ARITHMETIC 

#define REG_BG1_CNT		*(vu16*)(REG_BASE + 0x000A)	//!< Control over background 1
#define BG1_HOR_OFFSET	*(vu16*)(REG_BASE + 0x0014)	//!< Horizontal offset	| Write only | CANT BE UPDATED WITH THE '+=' OR '-=' ARITHMETIC 
#define BG1_VER_OFFSET	*(vu16*)(REG_BASE + 0x0016)	//!< Vertical offset	| Write only | CANT BE UPDATED WITH THE '+=' OR '-=' ARITHMETIC 

#define REG_BG2_CNT		*(vu16*)(REG_BASE + 0x000C)	//!< Control over background 2
#define BG2_HOR_OFFSET	*(vu16*)(REG_BASE + 0x0018)	//!< Horizontal offset	| Write only | CANT BE UPDATED WITH THE '+=' OR '-=' ARITHMETIC 
#define BG2_VER_OFFSET	*(vu16*)(REG_BASE + 0x001A)	//!< Vertical offset	| Write only | CANT BE UPDATED WITH THE '+=' OR '-=' ARITHMETIC 

#define REG_BG3_CNT		*(vu16*)(REG_BASE + 0x000E)	//!< Control over background 3
#define BG3_HOR_OFFSET	*(vu16*)(REG_BASE + 0x001C)	//!< Horizontal offset	| Write only | CANT BE UPDATED WITH THE '+=' OR '-=' ARITHMETIC 
#define BG3_VER_OFFSET	*(vu16*)(REG_BASE + 0x001E)	//!< Vertical offset	| Write only | CANT BE UPDATED WITH THE '+=' OR '-=' ARITHMETIC 

// A value for position is ment for the position of the SCREEN not the map. It is NOT the position of the map on the screen!
// If you increase the scrolling values, you move the screen to the right, which corresponds with the map moving left on the screen.
// MEANING IN MATH:
// ScreenPos + ScrollingOffset = MapPosition
// ScreenPos = MapPosition - ScrollingOffset

typedef u16 SCREEN_ENTRY;		//!< Stores the tilemap
typedef SCREEN_ENTRY	SCREENBLOCK[1024];	//!< Screenblock struct

typedef struct BG_OFFSET	//!< Regular map offsets
{
	s16 offsetX;
	s16 offsetY;
}ALIGN4 BG_OFFSET;

#define screen_entry_mem	((SCREENBLOCK*)VRAM)	//!< SCREEN_ENTRY_MEM maps out VRAM into screenblocks screem-entries, making finding a specific entry easier.

// For regular tilemaps, each screen entry is 16bits long. Besides the tile index, it contains flipping flags and a palette bank index for 4bpp / 16 color tiles. 
// The affine screen entries are only 8 bits wide and just contain an 8bit tile index.

INLINE COLOR RGB15(u32 red, u32 green, u32 blue);

INLINE COLOR RGB15(u32 red, u32 green, u32 blue)
{
	return red | (green << 5) | (blue << 10);
}

#define BACKGROUND_PALETTE_MEM	((COLOR*)MEM_PAL)

#endif // !GBA_BACKGROUND_DEF_H

