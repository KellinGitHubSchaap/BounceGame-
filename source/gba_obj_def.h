#ifndef GBA_OBJ_DEF_H
#define GBA_OBJ_DEF_H

#include "gba_type_def.h"
#include "gba_bitfield_def.h"
#include "gba_obj_attribute.h"

#define ALIGN4	__attribute__((aligned(4)))

typedef struct OBJ_ATTR
{
	u16 attr0;		//!< Y-position | setting roation/scaling on/off | double-size sprite data (0 == normal - 1 == double) | transparency | mosaic mode | use 16 (off == 4bpp) or 256(on == 8bpp) colors | (16x16)SQUARE == 00 - (32x16)WIDE == 01 - (16x32)TALL == 10
	u16 attr1;		//!< X-position | Horizontal sprite flip | Vertical sprite flip | set sprite rotation or scale | Sprite size (0 - 3)
	u16 attr2;		//!< Tile index	| Priority (0 == highest - 3 == lowest) | palette bank
	s16 fill;
} ALIGN4 OBJ_ATTR;

typedef struct OBJ_AFFINE
{
	u16 fill0[3];
	s16 pa;
	
	u16 fill1[3];
	s16 pb;
	
	u16 fill2[3];
	s16 pc;
	
	u16 fill3[3];
	s16 pd;

}ALIGN4 OBJ_AFFINE;

void OAM_Init(OBJ_ATTR* obj, u32 count);
void OAM_Copy(OBJ_ATTR* destination, const OBJ_ATTR* source, u32 count);

INLINE OBJ_ATTR* SetObjectAttributes(OBJ_ATTR* obj, u16 attr0, u16 attr1, u16 attr2);	//!< Set all atributes for this object
INLINE void SetObjectPosition(OBJ_ATTR* obj, u32 posX, u32 posY);							//!< Set object position
INLINE void HideObject(OBJ_ATTR* obj);														//!< Hide the given object
INLINE void UnhideObject(OBJ_ATTR* obj, u16 mode);											//!< Show the given object

INLINE OBJ_ATTR* SetObjectAttributes(OBJ_ATTR* obj, u16 attribute0, u16 attribute1, u16 attribute2)
{
	obj->attr0 = attribute0;
	obj->attr1 = attribute1;
	obj->attr2 = attribute2;

	return obj;
}

INLINE void SetObjectPosition(OBJ_ATTR* obj, u32 posX, u32 posY)
{
	SET_SHIFTED_BITFIELD(obj->attr0, posY, ATTR0_Y);
	SET_SHIFTED_BITFIELD(obj->attr1, posX, ATTR1_X);
}

INLINE void HideObject(OBJ_ATTR* obj)
{
	SET_BITFIELD(obj->attr0, ATTR0_OBJ_MODE_HIDE, ATTR0_OBJ_MODE);
}

INLINE void UnhideObject(OBJ_ATTR* obj, u16 mode)
{
	SET_BITFIELD(obj->attr0, mode, ATTR0_OBJ_MODE);
}

#define REG_OAM ((OBJ_ATTR*) 0x07000000)	//!< Object Attribute Memory

#endif // !GBA_OBJ_DEF_H
