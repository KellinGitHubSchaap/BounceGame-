#include "gba_tool_def.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE* obj_aff_buffer = (OBJ_AFFINE*)obj_buffer;

u16 currentBGOffsetY = 0;

bool bounce = false;
u32 addBounce;

u32 oam_index = 0;

class Sheep
{
public:
	u8 posX = 120, posY = 96;
	u32 tile = 0, paletteBank = 0;
	OBJ_ATTR* bouncySheepAttr = &obj_buffer[0];

	int width = 16, height = 16;
	int speed = 2;

	void Render()
	{
		SetObjectAttributes(&obj_buffer[oam_index], ATTR0_SHAPE_SQUARE, ATTR1_SIZE_16, ATTR2_PALETTE_BANK(paletteBank) | tile);
		SetObjectPosition(&obj_buffer[oam_index], posX, posY);
		oam_index++;
	}
};

class Platform
{
public:
	u8 posX = 0, posY = 144;
	u32 tile = 4, paletteBank = 1;
	OBJ_ATTR* platformAttr = &obj_buffer[1];

	int width = 16, height = 6;

	void Render()
	{
		SetObjectAttributes(&obj_buffer[oam_index], ATTR0_SHAPE_SQUARE, ATTR1_SIZE_16, ATTR2_PALETTE_BANK(paletteBank) | tile);
		SetObjectPosition(&obj_buffer[oam_index], posX, posY);
		oam_index++;
	}
};

#pragma region Sprite Code

void SetSprites()
{
	memcpy(&tile_mem[4][0], BouncySheep_4bppTiles, BouncySheep_4bppTilesLen);
	memcpy(&REG_OBJ_PAL4[0], BouncySheep_4bppPal, BouncySheep_4bppPalLen);

	memcpy(&tile_mem[4][4], GrassPlatform_4bppTiles, GrassPlatform_4bppTilesLen);
	memcpy(&REG_OBJ_PAL4[1], GrassPlatform_4bppPal, GrassPlatform_4bppPalLen);
}
#pragma endregion


#pragma region Background Code

void MoveBackground()
{
	currentBGOffsetY -= 1;
	BG0_VER_OFFSET = currentBGOffsetY;
}

void SetBackground()
{
	memcpy(BACKGROUND_PALETTE_MEM, newer_sky_tilemapPal, newer_sky_tilemapPalLen);
	memcpy(&tile_mem[0][0], newer_sky_tilemapTiles, newer_sky_tilemapTilesLen);
	memcpy(&screen_entry_mem[30][0], newer_sky_tilemapMap, newer_sky_tilemapMapLen);
}
#pragma endregion


void ResetOAM()
{
	memset(obj_buffer, 0, sizeof(obj_buffer));
	oam_index = 0;
}


std::array<Platform, 9> platformArray;

Platform CreatePlatform(u8 offset)
{
	Platform* plat = new Platform();
	plat->posX = offset;
	return *plat;
}

void MovePlatforms()
{
	for (u32 p = 0; p < platformArray.size(); p++)
	{
		platformArray[p].posY += 2;


		if (platformArray[p].posY > SCREEN_HEIGHT)
		{
			u32 value = qran_range(0, SCREEN_WIDTH - 16);
			platformArray[p].posX = value;
			platformArray[p].posY = 0;
		}
	}
}

int main()
{
	SetSprites();
	SetBackground();
	OAM_Init(obj_buffer, 128);

	REG_BG0_CNT = BG_CHARBLOCK_BASE(0) | BG_SCREENBLOCK_BASE(30) | BG_4BPP | BG_REGULAR_32x32;
	REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0;

	Sheep sheep;

	for (u32 i = 0; i < platformArray.size(); i++)
	{
		platformArray[i] = CreatePlatform(qran_range(0, SCREEN_WIDTH - 16));
	}

	while (1)
	{
		vid_sync();
		ScanKeys();

		ResetOAM();

		sheep.Render();

		if (GetKey(KEY_A))
		{
			MovePlatforms();
		}

		for (Platform& i : platformArray)
		{
			i.Render();
		}

		for (u32 p = 0; p < platformArray.size(); p++)
		{
			if (sheep.posX < platformArray[p].posX + platformArray[p].width &&
				sheep.posX + sheep.width > platformArray[p].posX &&
				sheep.posY < platformArray[p].posY + platformArray[p].height &&
				sheep.posY + platformArray[p].height > platformArray[p].posY /*&&
				bounce == false*/)
			{
				addBounce = sheep.posY - 64;
				bounce = true;
			}
		}

		if (sheep.posY > addBounce && bounce == true)
		{
			sheep.posY -= sheep.speed;
			MoveBackground();
			MovePlatforms();
		}
		else
		{
			sheep.posY += sheep.speed;

			if (sheep.posY > SCREEN_HEIGHT)
			{
				sheep.posY = 0;
			}

			if (bounce == true)
			{
				bounce = false;
				addBounce = 0;
			}
		}

		if (GetKey(KEY_RIGHT))
		{
			sheep.posX += 1;

			if (sheep.posX > SCREEN_WIDTH)
			{
				sheep.posX = 0;
			}

		}
		else if (GetKey(KEY_LEFT))
		{
			sheep.posX -= 1;

			if (sheep.posX < 0)
			{
				sheep.posX = SCREEN_WIDTH;
			}
		}

		OAM_Copy(REG_OAM, obj_buffer, oam_index);
	}

	return 0;
}
