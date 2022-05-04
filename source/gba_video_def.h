#ifndef GBA_VIDEO_DEF_H
#define GBA_VIDEO_DEF_H

#include "gba_base_def.h"

#define REG_DISPCNT	*((vu16*)(REG_BASE + 0x0000))	//!< controls all aspects of GBA display

#define DCNT_OBJ_1D 0x0040     //!< 1D sprite mapping mode

// === DCNT_MODE : Tiled === 
#define DCNT_MODE0	0x0000	//!< 4 tiled background layers | can't be scaled nor rotated | move only
#define DCNT_MODE1	0x0001	//!< 3 tiled background layers | 0 & 1 can't be scaled nor rotated | 2 can be scaled, rotated, and moved
#define DCNT_MODE2	0x0002	//!< 2 tiled background layers | full scaling, rotating and movement

// === DCNT_MODE : Bitmapped ===
#define DCNT_MODE3	0x0003	//!< 256 colors | 16-bit mapped (non-paletted) | 240x160 
#define DCNT_MODE4	0x0004	//!< 16 colors | 8-bit mapped | 240x160 | allows page-flipping
#define DCNT_MODE5	0x0005	//!< 256 colors | 16-bit mapped | 160x128 | screen buffering

// === BG : Layers ===
#define DCNT_BG0	0x0100	//!< can't be rotated/scaled | allows movement
#define DCNT_BG1	0x0200	//!< can't be rotated/scaled | allows movement
#define DCNT_BG2	0x0400	//!< can be rotated/scaled and allows movement
#define DCNT_BG3	0x0800	//!< can be rotated/scaled and allows movement
#define DCNT_OBJ	0x1000	//!< sprite object layer

#define REG_DISTAT	*((vu16*)(REG_BASE + 0x0004))	//!< A register that holds and controls LCD interupts

// Screen size
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

#define REG_VCOUNT	*(vu16*)0x04000006	//!< Vertical scanline counter 

INLINE void vid_sync()	//!< Alternative for VBlankIntrWait()
{
	while (REG_VCOUNT >= 160);	// wait till VDraw
	while (REG_VCOUNT < 160);	// wait till VBlank
}


#endif // !GBA_VIDEO_DEF_H
