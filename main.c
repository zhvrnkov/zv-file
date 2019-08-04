//
//  main.c
//  myfile
//
//  Created by Vlad Zhavoronkov on 8/1/19.
//  Copyright © 2019 Vlad Zhavoronkov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _writeStatus {
    int isSuccess;
} WriteStatus;

typedef struct _readStatus {
    int isSuccess;
    char *content;
} ReadStatus;

WriteStatus writeToFile(const char *path, const char *content);
ReadStatus readAllFromFile(const char *path);
ReadStatus readFromFile(const char *path, int amount);

char mockContent[] = "Lorem Ipsum Datur Uel";

int main(int argc, const char * argv[]) {
    WriteStatus writeResult = writeToFile("./text", mockContent);
    if (!writeResult.isSuccess) printf("error: bad write\n");
    ReadStatus readRestult = readAllFromFile("./text");
    if (readRestult.isSuccess) {
        if (!strcmp(readRestult.content, mockContent)) printf("error: bad content\n");
    } else {
        printf("error: bad read\n");
    }

    return 0;
}

WriteStatus writeToFile(const char *path, const char *content) {
    WriteStatus output = { 0 };
    return output;
}

ReadStatus readAllFromFile(const char *path) {
    ReadStatus output = { 0, NULL };
    return output;
}

ReadStatus readFromFile(const char *path, int amount) {
    ReadStatus output = { 0, NULL };
    return output;
}
