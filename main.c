#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.c"
#include "getfilesize.c"
#include "utils.c"

const char *files[] = {"file1.txt", "file2.txt", "file3.txt"};

int main() {
    Header header;

    size_t length = sizeof(files) / sizeof(files[0]);

    header.fileCounter = length;

    header.entries = (Entry *)malloc(sizeof(Entry) * header.fileCounter);

    // сохраняем название файлов в структуру
    for (int i = 0; i < header.fileCounter; i++) {
        strcpy(header.entries[i].fileName, files[i]);
        int fileSize = getFileSize(header.entries[i].fileName);
        header.entries[i].fileSize = fileSize;
    }

    printStructInfo(&header);

    int sizeOfHeaders = sizeof(header);

    printf("size of all headers: %d\n", sizeOfHeaders);

    for (int i = 0; i < header.fileCounter; i++) {
        if (i == 0) {
            header.entries[i].offset = sizeOfHeaders;
        } else {
            header.entries[i].offset = (header.entries[i-1].offset + header.entries[i-1].fileSize);
        }
    }

    printStructInfo(&header);

    FILE *newArchive = fopen("arch.txt", "wb");
    fwrite(&header.fileCounter, sizeof(header.fileCounter), 1, newArchive);
    fwrite(header.entries, sizeof(Entry), header.fileCounter, newArchive);

    for (int index = 0; index < header.fileCounter; index++) {

        char *buffer = (char *)malloc(header.entries[index].fileSize);

        FILE *file = fopen(header.entries[index].fileName, "rb");
        fread(buffer, 1, header.entries[index].fileSize, file);
        fwrite(buffer, 1, header.entries[index].fileSize, newArchive);

        free(buffer);
    }

    fclose(newArchive);


    





    printf("\n=========\n\n");

    Header newHeaders;
    FILE *readFile = fopen("arch.txt", "rb");

    fread(&newHeaders.fileCounter, sizeof(newHeaders.fileCounter), 1, readFile);

    printf("file counter %d\n", newHeaders.fileCounter); 

    newHeaders.entries = (Entry *)malloc(sizeof(Entry) * newHeaders.fileCounter);

    if (newHeaders.entries == NULL) {
        perror("Ошибка выделения памяти");
        fclose(readFile);
        return EXIT_FAILURE; // Завершаем программу в случае ошибки
    }

    // // Считываем записи
    if (fread(newHeaders.entries, sizeof(Entry), newHeaders.fileCounter, readFile) != newHeaders.fileCounter) {
        perror("Ошибка чтения записей");
        free(newHeaders.entries); // Освобождаем память перед выходом
        fclose(readFile);
        return EXIT_FAILURE; // Завершаем программу в случае ошибки
    }

    // // Закрываем файл
    fclose(readFile);

    // Вывод информации о заголовке и записях
    printf("new file counter: %d\n", newHeaders.fileCounter);
    printStructInfo(&newHeaders);

    // // Освобождаем выделенную память
    free(newHeaders.entries);




    return 0;
}