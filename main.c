//
//  main.c
//  myfile
//
//  Created by Vlad Zhavoronkov on 8/1/19.
//  Copyright © 2019 Vlad Zhavoronkov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "index.h"

const extern struct _flag FlagsStruct;

MYFILE *getiob() {
    MYFILE *output = (MYFILE *) malloc(sizeof(MYFILE) * OPEN_MAX);
    
    MYFILE _stdout = { 0, (char *) 0, (char *) 0, FlagsStruct._READ, 0 };
    MYFILE _stdin = { 0, (char *) 0, (char *) 0, FlagsStruct._WRITE, 1};
    MYFILE _stderr = { 0, (char *) 0, (char *) 0, FlagsStruct._WRITE | FlagsStruct._UNBUF, 2};
    
    output[0] = _stdout;
    output[1] = _stdin;
    output[2] = _stderr;
    
    return output;
};

MYFILE *_iob;

int main(int argc, const char * argv[]) {
    _iob = getiob();
    
    printf("Hello, World!\n");
    return 0;
}
