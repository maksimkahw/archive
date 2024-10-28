#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.c"
#include "getfilesize.c"
#include "utils.c"

char *getFileNameWithoutPath(char *);
int CreateArchive(Header, char *, char **);

int main(int argc, char **argv) {

    char **files = (char **)malloc(sizeof(char *) * (argc - 1));
    
    for (int i = 1; i < argc; i++) {
        files[i-1] = argv[i];
    }
    
    printf("\n\n\n%d", argc);

    for (int i = 0; i < argc-1; i++) {
        printf("\n%s\n", files[i]);
    }

    Header header;

    size_t length = argc - 1;

    header.fileCounter = length;

    header.entries = (Entry *)malloc(sizeof(Entry) * header.fileCounter);

    // сохраняем название файлов в структуру
    for (int i = 0; i < header.fileCounter; i++) {
        char *fileNamess = getFileNameWithoutPath(files[i]);

        strcpy(header.entries[i].fileName, fileNamess);

        int fileSize = getFileSize(files[i]);

        header.entries[i].fileSize = fileSize;
    }

    printStructInfo(&header);

    printf("----------\n");

    int sizeOfHeaders = sizeof(header.fileCounter) + (sizeof(Entry) * header.fileCounter);

    printf("size of all headers: %d\n", sizeOfHeaders);
    printf("----------\n");

    for (int i = 0; i < header.fileCounter; i++) {
        if (i == 0) {
            header.entries[i].offset = sizeOfHeaders;
        } else {
            header.entries[i].offset = (header.entries[i-1].offset + header.entries[i-1].fileSize);
        }
    }

    printStructInfo(&header);

    CreateArchive(header, "arch.zh", files);
    
    return 0;
}

char *getFileNameWithoutPath(char *fileName) {
    int index = 0;
    int position = -1;
    int lenth = strlen(fileName);
    int size;

    while (fileName[index] != '\0') {
        if (fileName[index] == '/') {
            position = index;
        }
        index++;
    }

    if (position == -1)
        return fileName;

    position++;

    size = lenth - position + 1;

    char *buffer = (char *)malloc(sizeof(char) * 64);
    if (buffer == NULL) {
        printf("НЕ УДАЛОСЬ ВЫДЕЛИТЬ ПАМЯТЬ");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        buffer[i] = fileName[position+i];
        printf("%c\t%d\n", buffer[i], i);
    }

    for (int i = size; i < 64; i++) {
        buffer[i] = '0';
    }

    buffer[size-1] = '\0';

    return buffer;
}

int CreateArchive(Header header, char *fileName, char *files[]) {
    FILE *newArchive = fopen("arch.txt", "wb");
    fwrite(&header.fileCounter, sizeof(header.fileCounter), 1, newArchive);
    fwrite(header.entries, sizeof(Entry), header.fileCounter, newArchive);

    for (int index = 0; index < header.fileCounter; index++) {

        char *buffer = (char *)malloc(header.entries[index].fileSize);

        FILE *file = fopen(files[index], "rb");

        fread(buffer, 1, header.entries[index].fileSize, file);

        fwrite(buffer, 1, header.entries[index].fileSize, newArchive);

        free(buffer);
        fclose(file);
    }

    fclose(newArchive);
}