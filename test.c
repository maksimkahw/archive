#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    char **files = (char **)malloc(sizeof(char *) * (argc - 1)); // = {"file1.txt", "file2.txt", "file3.txt"};


    for (int i = 1; i < argc; i++) {
        files[i-1] = argv[i];
    }

    for (int i = 1; i < argc-1; i++) {
        printf("%s\n", files[i]);
    }

    char string[] = "pr";
    printf("%ld \n", strlen(string));
    return 0;
}