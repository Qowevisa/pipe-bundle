#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            fprintf(stdout, "%s", buff);
        }
        for (int i = 1; i < argc; i++) {
            fprintf(stdout, "%s\n", argv[i]);
        }
    }
    return 0;
}
