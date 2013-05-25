#pragma once

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <exec/types.h>

#define MODE_OLDFILE (int)"r+"
#define MODE_NEWFILE (int)"w"
#define MODE_READWRITE (int)"w+"

enum {
	OFFSET_CURRENT = SEEK_CUR,
	OFFSET_BEGINNING = SEEK_SET,
	OFFSET_END = SEEK_END,
};

static inline BPTR Open( CONST_STRPTR name, int accessMode )
	/* Open a file for read or write */
{
	return (BPTR)fopen(name, (const char*)accessMode);
}

static inline LONG Close( BPTR file )
	/* Close a file */
{
	return fclose((FILE*)file);
}

static inline LONG Read( BPTR file, APTR buffer, LONG length )
	/* Read n bytes into a buffer (unbuffered) */
{
	return fread(buffer, length, 1, (FILE*)file);
}

static inline LONG Write( BPTR file, CONST APTR buffer, LONG length )
	/* Write n bytes into a buffer (unbuffered) */
{
	return fwrite(buffer, length, 1, (FILE*)file);
}

static inline LONG FPutC(BPTR file, char c)
{
	return fputc(c, (FILE*)file);
}

static inline int Flush(BPTR file)
{
	return fflush((FILE*)file);
}

static inline off_t Seek(BPTR file, off_t offset, int whence)
{
	return fseek((FILE*)file, offset, whence);
}

#define FPrintf(x, ...) fprintf((FILE*)x, __VA_ARGS__)
#define Printf printf

static inline LONG FPuts(BPTR file, STRPTR str)
{
	return fputs(str, (FILE*)file);
}

static inline const char* FGets(BPTR f, char* buffer, int len)
{
	return fgets(buffer, len, (FILE*)f);
}

static inline char FGetC(BPTR f)
{
	return fgetc((FILE*)f);
}

static inline void UnGetC(BPTR f, char c)
{
	ungetc(c, (FILE*)f);
}

static inline long StrToLong(char* str, LONG* result)
{
	char* end;
	*result = strtol(str, &end, 10);
	return end - str;
}

static inline void PutStr(const char* str)
{
	puts(str);
}

static inline int Strnicmp(const char* a, const char* b, int len)
{
	return strncasecmp(a,b, len);
}

static inline int Stricmp(const char* a, const char* b)
{
	return strcasecmp(a,b);
}

static inline BPTR Input()
{
	return (BPTR)stdin;
}

static inline BPTR Output()
{
	return (BPTR)stdout;
}

static inline char ToUpper(char c)
{
	return toupper(c);
}

static inline char ToLower(char c)
{
	return tolower(c);
}
