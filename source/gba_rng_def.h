#ifndef GBA_RNG_DEF_H
#define GBA_RNG_DEF_H

#include "gba_type_def.h"

//! \name Random numbers
//\{

#define QRAN_SHIFT 15
#define QRAN_MASK  ((1<<QRAN_SHIFT)-1)
#define QRAN_MAX   QRAN_MASK

u32 sqran(u32 seed);
INLINE u32 qran(void);
INLINE u32 qran_range(u32 min, u32 max);

//\}

extern u32 __qran_seed;

//! Quick (and very dirty) pseudo-random number generator 
/*! \return random in range [0,8000h>
*/
INLINE u32 qran(void)
{
	__qran_seed = 1664525 * __qran_seed + 1013904223;
	return (__qran_seed >> 16) & QRAN_MAX;
}


//! Ranged random number
/*! \return random in range [\a min, \a max>
*	\note (max-min) must be lower than 8000h
*/
INLINE u32 qran_range(u32 min, u32 max)
{
	return (qran() * (max - min) >> QRAN_SHIFT) + min;
}

#endif // !GBA_RNG_DEF_H

