#ifndef GBA_OBJ_ATTRIBUTE_H
#define GBA_OBJ_ATTRIBUTE_H

// === Attribute 0 ===

#define ATTR0_Y_MASK	0x00FF					//!< Y positioning
#define ATTR0_Y_SHIFT	0						//!< bit position in memory
#define ATTR0_Y(n)		((n) << ATTR0_Y_SHIFT)	//!< Shift the value of "n" to the bit position

#define ATTR0_OBJ_MODE_MASK			0x0300		//!< Object Mode
#define ATTR0_OBJ_MODE_SHIFT		8
#define ATTR0_OBJ_MODE(n)			((n) << ATTR0_OBJ_MODE_SHIFT)

#define ATTR0_OBJ_MODE_REGULAR			(0 << ATTR0_OBJ_MODE_SHIFT)		//!< Normal rendering			00 << 8
#define ATTR0_OBJ_MODE_AFFINE			(1 << ATTR0_OBJ_MODE_SHIFT)		//!< Affine sprite rendering	01 << 8
#define ATTR0_OBJ_MODE_HIDE				(2 << ATTR0_OBJ_MODE_SHIFT)		//!< Hide object				10 << 8
#define ATTR0_OBJ_MODE_AFFINE_DOUBLE	(3 << ATTR0_OBJ_MODE_SHIFT)		//!< Affine + double rendering	11 << 8

#define ATTR0_GFX_MODE_MASK			0x0C00	//!< Graphical settings
#define ATTR0_GFX_MODE_SHIFT		10
#define ATTR0_GFX_MODE(n)			((n) << ATTR0_GFX_MODE_SHIFT)

#define ATTR0_GFX_MODE_REGULAR		(0 << ATTR0_GFX_SHIFT)	//!< Normal graphics	00 << 10
#define ATTR0_GFX_MODE_BLEND		(1 << ATTR0_GFX_SHIFT)	//!< Blend graphics		01 << 10
#define ATTR0_GFX_MODE_WINDOW		(2 << ATTR0_GFX_SHIFT)	//!< Window graphics	10 << 10

#define ATTR0_MOSAIC_MASK			0x1000	//!< Object mosaic mode setting
#define ATTR0_MOSAIC_SHIFT			12
#define ATTR0_MOSAIC(n)				((n) << ATTR0_MOSAIC_SHIFT)

#define ATTR0_COLOR_MODE_MASK		0x2000	//!< Object color mode (4bpp (16 colors) - 8bpp (256 colors))
#define ATTR0_COLOR_MODE_SHIFT		13
#define ATTR0_COLOR_MODE(n)			((n) << ATTR0_COLOR_MODE_SHIFT)

#define ATTR0_COLOR_MODE_4BPP		(0x0000 << ATTR0_COLOR_MODE_SHIFT)	//!< 16 colors
#define ATTR0_COLOR_MODE_8BPP		(0x2000 << ATTR0_COLOR_MODE_SHIFT)	//!< 256 colors

#define ATTR0_SHAPE_MASK			0xC000	//!< Object shape setting
#define ATTR0_SHAPE_SHIFT			14
#define ATTR0_SHAPE(n)				((n) << ATTR0_SHAPE_SHIFT)

#define ATTR0_SHAPE_SQUARE			(0 << ATTR0_SHAPE_SHIFT)	//!< (00) 16x16 pixels	| the object is has even sides, like a square
#define ATTR0_SHAPE_WIDE			(1 << ATTR0_SHAPE_SHIFT)	//!< (01) 32x16 pixels	| the object has uneven sides,	like a bar
#define ATTR0_SHAPE_TALL			(2 << ATTR0_SHAPE_SHIFT)	//!< (10) 16x32 pixels	| the object has uneven sides,	like a tower

//! Attribute 0 builder
#define ATTR0_BUILD(y, shape, bpp, mode, mosaic, blend, window)          \
(                                                                        \
    ((y)&255) | (((mode)&3)<<8) | (((blend)&1)<<10) | (((window)&1)<<11) \
    | (((mosaic)&1)<<12) | (((bpp)&8)<<10) | (((shape)&3)<<14)           \
)

// === Attribute 1 ===

#define ATTR1_X_MASK	0x00FF	//!< X positioning
#define ATTR1_X_SHIFT	0		
#define ATTR1_X(n)		((n) << ATTR1_X_SHIFT)

#define ATTR1_AFFINE_MASK	0x0FE0	//!< Rotation and Scaling
#define ATTR1_AFFINE_SHIFT	9
#define ATTR1_AFFINE(n)		((n) << ATTR1_AFFINE_SHIFT)

#define ATTR1_FLIPH_MASK	0x1000	//!< Flip object horizontally
#define ATTR1_FLIPH_SHIFT	12
#define ATTR1_FLIPH(n)		((n) << ATTR1_FLIPH_SHIFT)

#define ATTR1_FLIPV_MASK	0x2000	//!< Flip object vertically
#define ATTR1_FLIPV_SHIFT	13
#define ATTR1_FLIPV(n)		((n) << ATTR1_FLIPV_SHIFT)

#define ATTR1_SIZE_MASK		0xC000	//!< Sprite size
#define ATTR1_SIZE_SHIFT	14
#define ATTR1_SIZE(n)		((n) << ATTR1_SIZE_SHIFT)

#define ATTR1_SIZE_8		(0x0000 << ATTR1_SIZE_SHIFT)	//!< 8x8 pixel sprite (00)
#define ATTR1_SIZE_16		(0x0001 << ATTR1_SIZE_SHIFT)	//!< 16x16 pixel sprite (01)
#define ATTR1_SIZE_32		(0x0002 << ATTR1_SIZE_SHIFT)	//!< 32x32 pixel sprite (10)
#define ATTR1_SIZE_64		(0x0003 << ATTR1_SIZE_SHIFT)	//!< 64x64 pixel sprite (11)

#define ATTR1_BUILD_REGULAR(x, size, hflip, vflip)         \
( ((x)&31) | (((hflip)&1)<<12) | (((vflip)&1)<<13) | (((size)&3)<<14) )

#define ATTR1_BUILD_AFFINE(x, size, affine_id)	\
(((x) & 31) | (((aff_id) & 31) << 9) | (((size) & 3) << 14))

// === Attribute 2 ===

#define ATTR2_TILE_INDEX_MASK	0x03FF	//!< Tile index mask
#define ATTR2_TILE_INDEX_SHIFT	0
#define ATTR2_TILE_INDEX(n)		((n) << ATTR2_TILE_INDEX_SHIFT)

#define ATTR2_PRIORITY_MASK		0x0C00	//!< Priority mask (0 == highest, 3 == lowest)
#define ATTR2_PRIORITY_SHIFT	10
#define ATTR2_PRIORITY(n)		((n) << ATTR2_PRIORITY_SHIFT)

#define ATTR2_PALETTE_BANK_MASK		0xF000	//!< Palette bank mask
#define ATTR2_PALETTE_BANK_SHIFT	12
#define ATTR2_PALETTE_BANK(n)		((n) << ATTR2_PALETTE_BANK_SHIFT)

#define ATTR2_BUILD(tileID, paletteBank, priority) \
(((tileID)&0x03FF) | (((paletteBank)&15)<<12) | (((priority)&3)<<10))


#endif // !GBA_OBJ_ATTRIBUTE_H
