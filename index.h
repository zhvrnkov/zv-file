//
//  index.h
//  myfile
//
//  Created by Vlad Zhavoronkov on 8/1/19.
//  Copyright © 2019 Vlad Zhavoronkov. All rights reserved.
//

#ifndef index_h
#define index_h

#include "unistd.h"
#include "flagsstruct.h"
#include <sys/fcntl.h>
#include <stdlib.h>

#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} MYFILE;

extern MYFILE *_iob;

#undef stdin
#undef stdout
#undef stderr

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p) (((p)->flag & FlagsStruct._EOF) != 0)
#define ferror(p) (((p)->flag & FlagsStruct._ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) (--(p)->cnt >= 0 \
? *(p)->ptr++ = (x) : _flsushbuf((x),p)

#define getchar() getc(stdin)
#define putchar(c) putc((x), stdout)

int myfillbuf(MYFILE *);
int myflushbuf(int, MYFILE *);
MYFILE *myfopen(char *, char *);
void myfclose(MYFILE *);
int myfseek(MYFILE *, long, int);
int myfflush(MYFILE *);
int myflose(MYFILE *);

#endif
