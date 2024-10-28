#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int getFileSize(const char* fileName) {
    printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!");
    printf("\n%s", fileName);
    struct stat fileStat;

    int fd = open(fileName, O_RDONLY);

    if (fstat(fd, &fileStat) == -1) {
        return -1;
    }

    if (fstat(fd, &fileStat) == -1) {
        close(fd);
        return -1;
    }

    close(fd);
    printf("\n%lld", (long long)fileStat.st_size);
    printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!");
    return ((long long)fileStat.st_size);
}