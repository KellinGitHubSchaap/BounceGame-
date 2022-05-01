#include "gba_obj_def.h"

void OAM_Init(OBJ_ATTR* obj, unsigned count)	//!< Initialize Object Attributes
{
	u32* destination = (u32*)obj;

	u32 iteration = count;
	while (iteration--)
	{
		*destination++ = ATTR0_OBJ_MODE_HIDE;
		*destination++ = 0;
	}

	OAM_Copy(REG_OAM, obj, count);
}

void OAM_Copy(OBJ_ATTR* destination, const OBJ_ATTR* source, unsigned count)
{
	while (count--)
	{
		*destination++ = *source++;
	}
}