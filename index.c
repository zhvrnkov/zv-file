//
//  index.c
//  myfile
//
//  Created by Vlad Zhavoronkov on 8/1/19.
//  Copyright © 2019 Vlad Zhavoronkov. All rights reserved.
//

#include "index.h"
#define PERMS 0666

const extern struct _flag FlagsStruct;

MYFILE *myfopen(char *filename, char *mode) {
    int fd;
    MYFILE *fp;
    
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (FlagsStruct._READ | FlagsStruct._WRITE)) == 0)
            break; /* found free slot */
    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;
    
    if (*mode == 'w')
        fd = creat(filename, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(filename, O_WRONLY, 0)) == -1)
            fd = creat(filename, PERMS);
        lseek(fd, 0L, 2); /* move cursor to end for future adding */
    } else
        fd = open(filename, O_WRONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? FlagsStruct._READ : FlagsStruct._WRITE;
    return fp;
}
