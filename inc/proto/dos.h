#pragma once

#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <exec/types.h>

#define MODE_OLDFILE (int)"r+"
#define MODE_NEWFILE (int)"w"
#define MODE_READWRITE (int)"w+"

enum {
	OFFSET_CURRENT = SEEK_CUR,
	OFFSET_BEGINING = SEEK_SET,
	OFFSET_BEGINNING = SEEK_SET,
	OFFSET_END = SEEK_END,
};

enum {
	SHARED_LOCK = F_RDLCK
};

static inline BPTR Open( CONST_STRPTR name, int accessMode )
	/* Open a file for read or write */
{
	return (BPTR)fopen(name, (const char*)accessMode);
}

static inline LONG Close( BPTR file )
	/* Close a file */
{
	return !fclose((FILE*)file);
}

static inline LONG Read( BPTR file, APTR buffer, LONG length )
	/* Read n bytes into a buffer (unbuffered) */
{
	return fread(buffer, 1, length, (FILE*)file);
}

static inline LONG Write( BPTR file, CONST APTR buffer, LONG length )
	/* Write n bytes into a buffer (unbuffered) */
{
	return fwrite(buffer, 1, length, (FILE*)file);
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
	fseek((FILE*)file, offset, whence);
	return ftell((FILE*)file);
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

static inline int FGetC(BPTR f)
{
	return fgetc((FILE*)f);
}

static inline void UnGetC(BPTR f, char c)
{
	ungetc(c, (FILE*)f);
}

static inline BPTR Lock(CONST_STRPTR name, int __attribute__((unused)) type)
{
	int fd = open(name, O_RDONLY|O_DIRECTORY);

	lockf(fd, F_LOCK, 0);

	return (BPTR)fd;
}

static inline void UnLock(BPTR fd)
{
	lockf((int)fd, F_ULOCK, 0);
	close((int)fd);
}

static inline BPTR CurrentDir(BPTR fd)
{
	static int cwd = 0;
	int old = cwd;

	fchdir((int)fd);
	cwd = (int)fd;

	return (BPTR)old;
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

enum {
	DOS_FIB
};

struct FileInfoBlock {
	struct stat st;
	DIR* D;
	struct dirent* d;

#define fib_DirEntryType st.st_mode & S_IFDIR ? 1:-1
#define fib_FileName d->d_name
#define fib_Size st.st_size
};


static inline void* AllocDosObject(int what, void* ptr)
{
	assert(ptr == NULL);
	size_t size;
	switch(what)
	{
		case DOS_FIB:
			size = sizeof(struct FileInfoBlock);
			break;
		default:
			assert(false);
	}
	return malloc(size);
}

static inline void FreeDosObject(int type, void* fib)
{
	assert(type == DOS_FIB);
	free(fib);
}

static inline void ExamineFH(BPTR file, struct FileInfoBlock* finfo)
{
	fstat(fileno((FILE*)file), &finfo->st);
}

static inline bool Examine(BPTR fd, struct FileInfoBlock* finfo)
{
	finfo->D = fdopendir((int)fd);
	return finfo->D != NULL;
}

static inline bool ExNext(BPTR fd, struct FileInfoBlock* finfo)
{
	assert(fd != NULL);

	finfo->d = readdir(finfo->D);

	if(finfo->d == NULL)
		return false;

	stat(finfo->d->d_name, &finfo->st);

	return true;
}
