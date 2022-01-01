#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int find(char *str, char delim) {
    int i = 0;
    while (str[i] != delim) {
        i++;
        if (str[i] == '\0') {
            return 0;
        }
    }
    return i;
}

#define MAX_CAP 1000
#define LINE_CAP 256

char arr[MAX_CAP][LINE_CAP] = {0};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: %s <STRING>\n", argv[0]);
    }
    int max = 0;
    char delim = argv[1][0];
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(LINE_CAP);
        size_t n;
        int tmp = 0;
        unsigned long counter = 0;
        while (getline(&buff, &n, stdin) != -1) {
            strcat(arr[counter++], buff);
            tmp = find(buff, delim);
            if (max < tmp) {
                max = tmp;
            }
        }
        //
        for (unsigned int i = 0; i < counter; i++) {
            if (find(arr[i], delim) == 0) {
                printf("%s", arr[i]);
                continue;
            }
            int j = 0;
            while (arr[i][j] != delim) {
                fputc(arr[i][j++], stdout);
            }
            int spaces = 0;
            while (j + spaces < max) {
                fputc(' ', stdout);
                spaces++;
            }
            while (arr[i][j] != '\n') {
                fputc(arr[i][j++], stdout);
            }
            fputc('\n', stdout);
        }
    }
    return 0;
}
