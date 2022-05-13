#include "log.h"

extern "C"
{
	extern bool logInitNocash(void)
	{
		for (u32 i = 0; i < 6; i++)
		{
			if ("no$gba"[i] != NOCASH_SIG[i])
			{
				return false;
			}
		}

		return true;
	}

	extern void logOutputNocash(u8 level, const char* message)
	{
		(void)level;

		while (*message)
		{
			REG_NOCASH_LOG = *message++;
		}

		REG_NOCASH_LOG = '\n';
	}
}