#include "gba_tool_def.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE* obj_aff_buffer = (OBJ_AFFINE*)obj_buffer;

u16 currentBGOffsetY = 96;

bool bounce = false;
u32 addBounce;

class Sheep
{
public:
	u8 posX = 120, posY = 96;
	u32 tile = 0, paletteBank = 0;
	OBJ_ATTR* bouncySheepAttr = &obj_buffer[0];

	int width = 16, height = 16;
	int speed = 2;
};

class Platform
{
public:
	u8 posX = 120, posY = 144;
	u32 tile = 4, paletteBank = 1;
	OBJ_ATTR* platformAttr = &obj_buffer[1];

	int width = 16, height = 6;
};

void MoveBackground()
{
	currentBGOffsetY -= 1;
	BG0_VER_OFFSET = currentBGOffsetY;
}

void SetObject()
{
	Sheep sheep;
	SetObjectAttributes(sheep.bouncySheepAttr, ATTR0_SHAPE_SQUARE, ATTR1_SIZE_16, ATTR2_PALETTE_BANK(sheep.paletteBank) | sheep.tile);
	SetObjectPosition(sheep.bouncySheepAttr, sheep.posX, sheep.posY);

	Platform platform;
	SetObjectAttributes(platform.platformAttr, ATTR0_SHAPE_SQUARE, ATTR1_SIZE_16, ATTR2_PALETTE_BANK(platform.paletteBank) | platform.tile);
	SetObjectPosition(platform.platformAttr, platform.posX, platform.posY);

	//Platform platform2;
	//platform2.platformAttr = &obj_buffer[2];
	//SetObjectAttributes(platform2.platformAttr, ATTR0_SHAPE_SQUARE, ATTR1_SIZE_16, ATTR2_PALETTE_BANK(platform2.paletteBank) | platform2.tile);
	//SetObjectPosition(platform2.platformAttr, platform2.posX, platform2.posY - 16);

	while (1)
	{
		vid_sync();
		ScanKeys();

		if (platform.posX < platform.posX + platform.width &&
			sheep.posX + sheep.width > platform.posX &&
			sheep.posY < platform.posY + platform.height &&
			sheep.posY + platform.height > platform.posY &&
			bounce != true)
		{
			addBounce = sheep.posY - 64;
			bounce = true;
		}

		if (sheep.posY > addBounce && bounce == true)
		{
			sheep.posY -= sheep.speed;
			MoveBackground();
		}
		else
		{
			sheep.posY += sheep.speed;

			if (bounce == true)
			{
				bounce = false;
				addBounce = 0;
			}
		}

		if (GetKey(KEY_RIGHT))
		{
			sheep.posX += 1;
		}
		else if (GetKey(KEY_LEFT))
		{
			sheep.posX -= 1;
		}

		SetObjectPosition(sheep.bouncySheepAttr, sheep.posX, sheep.posY);
		OAM_Copy(REG_OAM, obj_buffer, 2);
	}
}

void SetBackground()
{
	memcpy(BACKGROUND_PALETTE_MEM, newer_sky_tilemapPal, newer_sky_tilemapPalLen);
	memcpy(&tile_mem[0][0], newer_sky_tilemapTiles, newer_sky_tilemapTilesLen);
	memcpy(&screen_entry_mem[30][0], newer_sky_tilemapMap, newer_sky_tilemapMapLen);
}

int main()
{

	memcpy(&tile_mem[4][0], BouncySheep_4bppTiles, BouncySheep_4bppTilesLen);
	memcpy(&REG_OBJ_PAL4[0], BouncySheep_4bppPal, BouncySheep_4bppPalLen);
	
	memcpy(&tile_mem[4][4], GrassPlatform_4bppTiles, GrassPlatform_4bppTilesLen);
	memcpy(&REG_OBJ_PAL4[1], GrassPlatform_4bppPal, GrassPlatform_4bppPalLen);
	
	SetBackground();

	OAM_Init(obj_buffer, 128);

	REG_BG0_CNT = BG_CHARBLOCK_BASE(0) | BG_SCREENBLOCK_BASE(30) | BG_4BPP | BG_REGULAR_32x32;
	REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0;

	SetObject();

	while (1);

	return 0;
}


//TODO: Make one way collision happen
