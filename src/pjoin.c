#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RET_SIZE 102400

static inline void pjoin(FILE *file, char connector) {
    char *ret = (char*)malloc(RET_SIZE);
    memset(ret, 0, RET_SIZE);
    size_t pos = 0;
    //
    char *buff = (char*)malloc(2048);
    size_t n;
    while (getline(&buff, &n, file) != -1) {
        size_t i = 0;
        while (buff[i] != '\n') {
            ret[pos++] = buff[i++];
        }
        if (connector) {
            ret[pos++] = connector;
        } else {
            ret[pos++] = ' ';
        }
    }
    //
    ret[pos - 1] = '\0';
    printf("%s\n", ret);
}

int main(int argc, char *argv[]) {
    int fi = 0;
    char connector = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            fi = i + 1;
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            connector = argv[i + 1][0];
        }
    }
    //
    if (fi != 0) {
        // reading from file
        // validating
        struct stat buffer;
        if (stat(argv[fi], &buffer) != 0) {
            fprintf(stderr, "%s: %s: %s\n", argv[0], argv[fi], strerror(errno));
            return 1;
        }
        if (!S_ISREG(buffer.st_mode)) {
            fprintf(stderr, "%s: %s: Not a regular file\n", argv[0], argv[fi]);
            return 1;
        }
        FILE *file = fopen(argv[fi], "r");
        if (file == NULL) {
            fprintf(stderr, "%s: %s: %s\n", argv[0], argv[fi], strerror(errno));
            return 1;
        }
        //
        pjoin(file, connector);
    } else {
        // reading from stdin
        if (!isatty(fileno(stdin))) {
            pjoin(stdin, connector);
        }
    }
    return 0;
}
