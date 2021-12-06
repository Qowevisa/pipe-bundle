#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            char *tmp = (char*)malloc(4096);
            if (argc > 1) {
                strcat(tmp, argv[1]);
            }
            strcat(tmp, buff);
            tmp[strlen(tmp) - 1] = 0;
            if (argc > 2) {
                strcat(tmp, argv[2]);
            }
            tmp[strlen(tmp)] = '\n';
            fprintf(stdout, "%s", tmp);
        }
    }
    return 0;
}
