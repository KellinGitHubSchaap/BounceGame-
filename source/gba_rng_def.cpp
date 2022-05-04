#include "gba_rng_def.h"
#include "gba_type_def.h"

u32 __qran_seed = 42;

u32 sqran(u32 seed)
{
	u32 old = __qran_seed;
	__qran_seed = seed;
	return old;
}
