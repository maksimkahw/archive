#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "headers.c"

void printStructInfo(Header *header) {
    for (int i = 0; i < header->fileCounter; i++) {
        printf("file name: %s\n", header->entries[i].fileName);
        printf("file offset: %d\n", header->entries[i].offset);
        printf("file size: %llu\n", header->entries[i].fileSize);
    }
}