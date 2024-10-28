#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivator/headers.c"
#include "archivator/utils.c"

int parseHeadersAndCreateFiles(FILE *archive, Header header) {
    for (int index = 0; index < header.fileCounter; index++) {

        if (fseek(archive, header.entries[index].offset, SEEK_SET) != 0) {
            perror("Ошибка перемещения указателя файла");
            fclose(archive);
            return -1;
        }

        printf("\nfile pointer: %li\n", ftell(archive));

        char *buffer = (char *)malloc(sizeof(char) * header.entries[index].fileSize);

        fread(buffer, 1, header.entries[index].fileSize, archive);

        FILE *newFile = fopen(header.entries[index].fileName, "wb");

        fwrite(buffer, 1, header.entries[index].fileSize, newFile);

        printf("\nOffset: %d, File Size: %lld\n", header.entries[index].offset, header.entries[index].fileSize);

        fclose(newFile);

        printf("Success: file %s was parsing and create!\n", header.entries[index].fileName);
    }
}

int main(int argc, char **argv) {
    Header header;
    FILE *archive = fopen(argv[1], "rb");

    fread(&header.fileCounter, sizeof(header.fileCounter), 1, archive);

    printf("files: %d\n\n", header.fileCounter);

    header.entries = (Entry *)malloc(sizeof(Entry) * header.fileCounter);
    if (header.entries == NULL) {
        perror("Cant memory alloc");
        return -1;
    }

    fread(header.entries, sizeof(Entry), header.fileCounter, archive);

    printStructInfo(&header);
    
    printf("\n%li\n", ftell(archive));

    parseHeadersAndCreateFiles(archive, header);
 
    fclose(archive);

}