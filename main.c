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
#define file "./text"

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
WriteStatus overwriteFile(const char *path, const char *content);
ReadStatus readAllFromFile(const char *path);
ReadStatus readFromFile(const char *path, IntRange range);
CleanStatus cleanFile(const char *path);
void *arraySlice(const void *array, size_t sizeOfElement, IntRange range);

char mockContent[] = "Lorem Ipsum Uel\n";

void checkClean(void);
void checkWriteAndRead(void);
void checkReadInRange(void);

int main(int argc, const char * argv[]) {
    checkClean();
    checkWriteAndRead();
    checkReadInRange();
    
    return 0;
}

void checkClean() {
    int isSuccess = 1;
    writeToFile(file, "Just foo");
    CleanStatus cleanResult = cleanFile(file);
    if (!cleanResult.isSuccess) {
        printf("error: bad clean");
        isSuccess = 0;
    }
    ReadStatus readAfterClean = readAllFromFile(file);
    if (readAfterClean.isSuccess) {
        if (strcmp("", readAfterClean.content) != 0) {
            printf("error: bad clean check");
            isSuccess = 0;
        }
    } else {
        printf("error: bad read after clean\n");
        isSuccess = 0;
    }
    if (isSuccess) printf("success: checkClean\n");
}

void checkWriteAndRead() {
    int isSuccess = 1;
    cleanFile(file);
    WriteStatus writeResult = writeToFile(file, mockContent);
    if (!writeResult.isSuccess) {
        printf("error: bad write\n");
        isSuccess = 0;
    }
    ReadStatus wholeRead = readAllFromFile(file);
    if (wholeRead.isSuccess) {
        if (strcmp(wholeRead.content, mockContent) != 0) {
            printf("error: bad content\n");
            isSuccess = 0;
        }
    } else {
        printf("error: bad read\n");
        isSuccess = 0;
    }
    if (isSuccess) printf("success: checkWriteAndRead\n");
}

void checkReadInRange(void) {
    int isSuccess = 1;
    overwriteFile(file, mockContent);
    IntRange range = { 0, 5 };
    char *mockContentSlice = slice(mockContent, range);
    ReadStatus partialRead = readFromFile(file, range);
    if (partialRead.isSuccess) {
        if (strcmp(mockContentSlice, partialRead.content) != 0) {
            printf("error: bad read from file");
            isSuccess = 0;
        }
    } else {
        isSuccess = 0;
    }
    if (isSuccess) printf("success: checkReadInRange\n");
}

WriteStatus writeToFile(const char *path, const char *content) {
    WriteStatus output = { 0 };
    int fd = open(path, O_WRONLY);
    size_t numberOfWritenCharacters = write(fd, content, strlen(content));
    close(fd);
    if (numberOfWritenCharacters > 0)
        output.isSuccess = 1;
    return output;
}

WriteStatus overwriteFile(const char *path, const char *content) {
    cleanFile(path);
    return writeToFile(path, content);
}

ReadStatus readAllFromFile(const char *path) {
    ReadStatus output = { 0, NULL };
    int fd = open(path, O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    size_t numberOfReadCharacters = read(fd, buffer, size + 1);
    close(fd);
    if (numberOfReadCharacters != -1) {
        buffer[size] = '\0';
        output.isSuccess = 1;
        output.content = buffer;
    }
    return output;
}

ReadStatus readFromFile(const char *path, IntRange range) {
    ReadStatus output = { 0, NULL };
    int fd = open(path, O_RDONLY);
    int readAmount = range.upperBound - range.lowerBound;
    char *buffer = (char *)malloc(readAmount + 1);
    lseek(fd, range.lowerBound, SEEK_SET);
    size_t numberOfReadCharacters = read(fd, buffer, readAmount);
    close(fd);
    if (numberOfReadCharacters != -1) {
        buffer[readAmount] = '\0';
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
