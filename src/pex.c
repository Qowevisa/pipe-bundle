#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void pex(int argc, char *argv[], char *buff) {
    int pass = 1;
    for (int i = 1; i < argc; i++) {
        if (strstr(buff, argv[i]) != NULL) {
            pass = 0;
            break;
        }
    }
    if (pass) {
            fprintf(stdout, "%s", buff);
    }
}

extern int errno;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: pex PATTERNS [FILE]\n");
        return 1;
    }
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            pex(argc, argv, buff);
        }
    } else {
        struct stat buffer;
        if (stat(argv[argc - 1], &buffer) != 0) {
            fprintf(stderr, "pex: %s: %s\n", argv[argc - 1], strerror(errno));
            return 1;
        }
        if (!S_ISREG(buffer.st_mode)) {
            fprintf(stderr, "pex: %s: Not a regular file\n", argv[argc - 1]);
            return 1;
        }
        FILE *file = fopen(argv[argc - 1], "r");
        if (file == NULL) {
            fprintf(stderr, "pex: %s: %s\n", argv[argc - 1], strerror(errno));
            return 1;
        }
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, file) != -1) {
            pex(argc, argv, buff);
        }
    }
    return 0;
}
