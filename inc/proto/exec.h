#pragma once

#include <libgen.h>
#include <string.h>

#include <OS.h>

#include <exec/types.h>

enum {
	MEMF_PUBLIC = B_FULL_LOCK,	
	MEMF_ANY = 0, // Chip-RAM doesn't exist on Haiku
	MEMF_CLEAR = 0, // FIXME is that ok ? does create_area always clear ram ?
};

static inline void* AllocVec(ULONG byteSize, ULONG attributes)
{
	void* addr = NULL;
	create_area("AllocVec", &addr, B_ANY_ADDRESS, byteSize, attributes, B_READ_AREA|B_WRITE_AREA);
	return addr;
}

static inline void FreeVec(void* area)
{
	delete_area(area_for(area));
}

static inline void* AllocMem(ULONG byteSize, __attribute__((unused)) ULONG attributes)
{
	return calloc(1, byteSize);
}

static inline void FreeMem(void* address, __attribute__((unused)) int size)
{
	free(address);
}

static inline void CopyMem(APTR src, APTR dest, LONG size)
{
	memcpy(dest, src, size);
}

static inline void CopyMemQuick(APTR src, APTR dest, LONG size)
{
	memcpy(dest, src, size);
}

static inline const char* FilePart(char* source)
{
	return basename(source);
}
