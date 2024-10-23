#pragma once

typedef struct {
    char fileName[64];
    unsigned long long int fileSize;
    unsigned int offset;
} Entry;

typedef struct {
    unsigned int fileCounter;
    Entry *entries;
} Header;