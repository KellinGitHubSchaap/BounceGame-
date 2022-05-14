#include "gba_tool_def.h"

OBJ_ATTR obj_buffer[128];								//!< Total buffersize of the GBA
OBJ_AFFINE* obj_aff_buffer = (OBJ_AFFINE*)obj_buffer;	//!< Total buffersize of the GBA with object that are affined 
u32 oam_index = 0;										//!< Used to get/set OAM Size 

#pragma region Classes

bool isBouncing = false;	//!< Is the sheep currently in bounce mode
u8 bounceStrength = 48;		//!< bounceStrength is going to be added to the current Y position of the Sheep
u8 bounceHeight;			//!< bounceHeight is a combo of the current sheep position and the strength of the jump 

class Sheep
{
public:
	u8 posX = 120, posY = 96;
	u32 tile = 0, paletteBank = 0;
	OBJ_ATTR* bouncySheepAttr = &obj_buffer[0];

	u8 width = 16, height = 16;
	u8 fallSpeed = 2;
	u8 horizontalSpeed = 1;

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

	u8 width = 16, height = 6;
	u8 spawnWidth = 24;
	u8 platformOffsetY = 32;

	u8 platformID;

	void Render()
	{
		SetObjectAttributes(&obj_buffer[oam_index], ATTR0_SHAPE_SQUARE, ATTR1_SIZE_16, ATTR2_PALETTE_BANK(paletteBank) | tile);
		SetObjectPosition(&obj_buffer[oam_index], posX, posY);
		platformID = oam_index;
		oam_index++;
	}
};

#pragma endregion

#pragma region SetSprites(), SetBackground(), and ResetOAM() functions

// Set up all settings of the sprites in memory 
void SetSprites()
{
	memcpy(&tile_mem[4][0], BouncySheep_4bppTiles, BouncySheep_4bppTilesLen);
	memcpy(&REG_OBJ_PAL4[0], BouncySheep_4bppPal, BouncySheep_4bppPalLen);

	memcpy(&tile_mem[4][4], GrassPlatform_4bppTiles, GrassPlatform_4bppTilesLen);
	memcpy(&REG_OBJ_PAL4[1], GrassPlatform_4bppPal, GrassPlatform_4bppPalLen);
}

// Set up the background in memory
void SetBackground()
{
	memcpy(BACKGROUND_PALETTE_MEM, newer_sky_tilemapPal, newer_sky_tilemapPalLen);
	memcpy(&tile_mem[0][0], newer_sky_tilemapTiles, newer_sky_tilemapTilesLen);
	memcpy(&screen_entry_mem[30][0], newer_sky_tilemapMap, newer_sky_tilemapMapLen);
}

// Refresh the Object Attribute Memory
void ResetOAM()
{
	memset(obj_buffer, 0, sizeof(obj_buffer));
	oam_index = 0;
}

#pragma endregion

#pragma region CreatePlatform function

std::array<Platform, 12> platformArray;		//!< The PlatformArray is used to store objects with the type class PLATFORM
u8 platformArraySpot = 0;					//!< Since I want to use a 2D array, I need to store at what position I am at within the PlatformArray

char posXDebug[300];

// Platform CreatePlatform() is called at the start of the game, its job is to place an X amount platforms across the screen 
Platform CreatePlatform(u32 offsetY)
{
	bool collision = false;

	do
	{
		u32 randomPosX = qran_range(0, SCREEN_WIDTH - platformArray[platformArraySpot].width);
		collision = false;

		for (u32 i = 0; i < platformArray.size(); i++)
		{
			if (((randomPosX + platformArray[platformArraySpot].width) < platformArray[i].posX) || (randomPosX > (platformArray[i].posX + platformArray[i].width)))
			{
				platformArray[platformArraySpot].posX = randomPosX;
				platformArray[platformArraySpot].posY = offsetY;

				return platformArray[platformArraySpot];
				
				continue;
			}
			else
			{
				collision = true;
				break;
			}
		}
	} while (collision);
}



//TODO: Fix the spawning of the platforms | Overlap is still present

#pragma endregion

#pragma region MoveBackground and MovePlatforms functions

u16 currentBGOffsetY = 0;	//!< Current offset of the background

// MoveBackground will move the background at the same time that the sheep is in a state of bouncing 
void MoveBackground()
{
	currentBGOffsetY -= 1;
	BG0_VER_OFFSET = currentBGOffsetY;
}

Platform* currentHitPlatform;	//!< Current collision with a platform
Platform* lastHitPlatform;		//!< Last known collision based on platform type
bool moveTheWorld = false;

// MovePlatforms() function is used to move all the platforms on screen when the sheep is in a bounce state and the (bool isBouncing = true)
// It also gives the platforms a new X position everytime they wrap around the screen.
void MovePlatforms()
{
	for (u32 p = 0; p < platformArray.size(); p++)
	{
		platformArray[p].posY += 2;

		if (platformArray[p].posY > SCREEN_HEIGHT + 48)
		{
			u32 randomXPos = qran_range(0, SCREEN_WIDTH - 16);
			platformArray[p].posX = randomXPos;
			platformArray[p].posY = 0;
		}
	}
}

#pragma endregion

char curPlatBuffer[100];
char lasPlatBuffer[100];

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
		platformArray[i] = Platform();
	}

	// Spawn the amount that the platformArray is able to store (standard is 12 in a 3x4 set up)
	for (u8 y = 0; y < 4; y++)
	{
		for (u8 x = 0; x < 3; x++)
		{
			platformArray[platformArraySpot] = CreatePlatform(y * 32);
			platformArraySpot++;
		}
	}

	while (1)
	{
		vid_sync();
		ScanKeys();
		ResetOAM();

		sheep.Render();

		for (Platform& i : platformArray)
		{
			i.Render();
		}

		if (GetKey(KEY_A))
		{
			MovePlatforms();
		}

		//When the sheep hits a platform:
		//1. Check if this platform has already been touched before
		//2. If this platform is new calculate the new height the sheep needs to travel to
		//3. Set the last platform known platform to be the current one that is touched
		//4. Make the currentPlatform that is touched null
		//5. Set MoveWorld and IsBouncing to be true

		for (u32 p = 0; p < platformArray.size(); p++)
		{
			if (sheep.posX < platformArray[p].posX + platformArray[p].width &&
				sheep.posX + sheep.width > platformArray[p].posX &&
				sheep.posY < platformArray[p].posY + platformArray[p].height &&
				sheep.posY + platformArray[p].height > platformArray[p].posY &&
				isBouncing == false)
			{

				currentHitPlatform = &platformArray[p];


				if (currentHitPlatform != lastHitPlatform)
				{
					/*isBouncing = true;
					bounceHeight = sheep.posY - bounceStrength;*/
					lastHitPlatform = &platformArray[p];

					snprintf(curPlatBuffer, sizeof(curPlatBuffer), "currentHitPlatform = %i", currentHitPlatform);
					snprintf(lasPlatBuffer, sizeof(lasPlatBuffer), "lastHitPlatform = %i", lastHitPlatform);

					if (logInitNocash())
					{
						logOutputNocash(0, curPlatBuffer);
						logOutputNocash(0, lasPlatBuffer);
					}
				}
				//	else
				//	{
				//		moveTheWorld = true;
				//		lastHitPlatform = currentHitPlatform;

				//		isBouncing = true;
				//		bounceHeight = sheep.posY - bounceStrength;
				//	}
			}
		}

		if (sheep.posY > bounceHeight && isBouncing == true)
		{
			sheep.posY -= sheep.fallSpeed;

			if (moveTheWorld)
			{
				MoveBackground();
				MovePlatforms();
			}
		}
		else
		{
			if (isBouncing == true)
			{
				isBouncing = false;
				moveTheWorld = false;
				bounceHeight = 0;
			}

			//	sheep.posY += sheep.fallSpeed;
			//	if (sheep.posY > SCREEN_HEIGHT) { sheep.posY = 0; }		// TODO: SHEEP DIES
		}

		if (GetKey(KEY_RIGHT))
		{
			sheep.posX += sheep.horizontalSpeed;
			if (sheep.posX > SCREEN_WIDTH) { sheep.posX = 0; }
		}
		else if (GetKey(KEY_LEFT))
		{
			sheep.posX -= sheep.horizontalSpeed;
			if (sheep.posX < 0) { sheep.posX = SCREEN_WIDTH; }
		}

		if (GetKey(KEY_DOWN))
		{
			sheep.posY += sheep.horizontalSpeed;
			if (sheep.posX > SCREEN_WIDTH) { sheep.posX = 0; }
		}
		else if (GetKey(KEY_UP))
		{
			sheep.posY -= sheep.horizontalSpeed;
			if (sheep.posX < 0) { sheep.posX = SCREEN_WIDTH; }
		}

		OAM_Copy(REG_OAM, obj_buffer, oam_index);
	}

	return 0;
}
