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
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

#define slice(array, range) (typeof(array[0]) *)arraySlice(array, sizeof(array[0]), range)

typedef char Byte;

typedef struct _writeStatus {
    int isSuccess;
} WriteStatus;

typedef struct _readStatus {
    int isSuccess;
    char *content;
} ReadStatus;

typedef struct _cleanStatus {
    int isSuccess;
} CleanStatus;

typedef struct _intRange {
    int lowerBound;
    int upperBound;
} IntRange;

WriteStatus writeToFile(const char *path, const char *content);
ReadStatus readAllFromFile(const char *path);
ReadStatus readFromFile(const char *path, int amount);
CleanStatus cleanFile(const char *path);
void *arraySlice(const void *array, size_t sizeOfElement, IntRange range);

char mockContent[] = "Lorem Ipsum Uel Datur\n";

int main(int argc, const char * argv[]) {
//    WriteStatus writeResult = writeToFile("./text", mockContent);
//    if (!writeResult.isSuccess) printf("error: bad write\n");
//    ReadStatus readRestult = readAllFromFile("./text");
//    if (readRestult.isSuccess) {
//        if (strcmp(readRestult.content, mockContent) != 0) printf("error: bad content\n");
//    } else {
//        printf("error: bad read\n");
//    }
    IntRange range = { 0, 11 };
    int array[] = { 1, 2, 3, 4, 5 };
    typeof(mockContent[0]) *slice = slice(mockContent, range);

    for (int i = 0; slice[i] != 0; i++)
        printf("%d ", slice[i]);
    
    printf("\n");
    return 0;
}

WriteStatus writeToFile(const char *path, const char *content) {
    WriteStatus output = { 0 };
    cleanFile(path);
    int fd = open(path, O_WRONLY);
    size_t numberOfWritenCharacters = write(fd, content, strlen(content));
    close(fd);
    if (numberOfWritenCharacters > 0)
        output.isSuccess = 1;
    return output;
}

ReadStatus readAllFromFile(const char *path) {
    ReadStatus output = { 0, NULL };
    int fd = open(path, O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *buffer = (char *)malloc(size);
    size_t numberOfReadCharacters = read(fd, buffer, size);
    close(fd);
    if (numberOfReadCharacters > 0) {
        output.isSuccess = 1;
        output.content = buffer;
    }
    return output;
}

ReadStatus readFromFile(const char *path, int amount) {
    ReadStatus output = { 0, NULL };
    int fd = open(path, O_RDONLY);
    char *buffer = (char *)malloc(amount);
    size_t numberOfReadCharacters = read(fd, buffer, amount);
    close(fd);
    if (numberOfReadCharacters > 0) {
        output.isSuccess = 1;
        output.content = buffer;
    }
    return output;
}

CleanStatus cleanFile(const char *path) {
    CleanStatus output = { 0 };
    if (truncate(path, 0) == 0)
        output.isSuccess = 1;
    return output;
}

void *arraySlice(const void *array, size_t sizeOfElement, IntRange range) {
    Byte *slice = (Byte *)malloc((range.upperBound - range.lowerBound) + 1 * sizeOfElement);
    int sliceIndex = 0;
    for (int i = range.lowerBound; i < range.upperBound; i++)
        for (long k = i * sizeOfElement; k < (i + 1) * sizeOfElement; k++, sliceIndex++)
            slice[sliceIndex] = ((Byte *)array)[k];
    for (int i = 0; i < sizeOfElement; i++, sliceIndex++)
        slice[sliceIndex] = 0;
    return slice;
}
