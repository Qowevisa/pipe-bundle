#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            buff[strlen(buff) - 1] = '\0';
            struct stat buffer;
            if (stat(buff, &buffer) != 0) {
                continue;
            }
            if (!S_ISDIR(buffer.st_mode)) {
                continue;
            }
            printf("%s\n", buff);
        }
    }
    return 0;
}
