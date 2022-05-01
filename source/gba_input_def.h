#ifndef GBA_INPUT_DEF_H
#define GBA_INPUT_DEF_H

#include "gba_type_def.h"
#include "gba_base_def.h"

#define REG_KEYINPUT	*(vu16*)(REG_BASE + 0x0130)	//!< Key Input
#define REG_KEYCNT		*(vu16*)(REG_BASE + 0x0132)	//!< Key Control
#define KEY_MASK		0x03FF

typedef enum KEYPAD_BITS
{
	key_a = 0, key_b, 
	key_right, key_left, key_up, key_down, 
	key_r, key_l,
	key_select, key_start
}KEYPAD_BITS;

#define KEY_A			0x0001	//!< Button A
#define KEY_B			0x0002	//!< Button B
#define KEY_SELECT		0x0004	//!< Select button
#define KEY_START		0x0008	//!< Start button
#define KEY_RIGHT		0x0010	//!< Right D-pad
#define KEY_LEFT		0x0020	//!< Left D-pad
#define KEY_UP			0x0040	//!< Up D-pad
#define KEY_DOWN		0x0080	//!< Down D-pad
#define KEY_R			0x0100	//!< Shoulder R
#define KEY_L			0x0200	//!< Shoulder L

#define CURRENT_KEY_DOWN(key)	(~(REG_KEYINPUT) & key)	//!< Which key is held down
#define CURRENT_KEY_UP(key)		((REG_KEYINPUT) & key)	//!< Which key is held up

extern u16 __current_key;
extern u16 __previous_key;

INLINE void ScanKeys();	//!< Check the state of all keys on the GBA

u32 GetKey(u32 key);			//!< Outputs a value as long as the key is held down 
u32 GetKeyDown(u32 key);		//!< Outputs once if the key is held down
u32 GetKeyUp(u32 key);		//!< Outputs once if the key is released

INLINE void ScanKeys()
{
	__previous_key = __current_key;
	__current_key = ~REG_KEYINPUT & KEY_MASK;
}

#endif // !GBA_INPUT_DEF_H

