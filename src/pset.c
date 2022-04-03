#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

enum states {
    length = 1
};

int main(int argc, char *argv[]) {
    uint8_t state = 0;
    for (int i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            uint32_t si = 0;
            char c;
            while (argv[i][si] != '\0') {
                c = argv[i][si++];
                switch (c) {
                    case 'l':
                        state |= length;
                        break;
                }
            }
        }
    }
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(2048);
        char *set = (char*)malloc(2048);
        size_t i, k, n;
        uint8_t unique;
        while (getline(&buff, &n, stdin) != -1) {
            i = 0;
            k = 0;
            while (buff[i] != '\n') {
                unique = 1;
                for (size_t si = 0; si < k; si++) {
                    if (buff[i] == set[si]) {
                        unique = 0;
                        break;
                    }
                }
                if (unique) {
                    set[k++] = buff[i];
                }
                i++;
            }
            if (state & length) {
                printf("%lu ", k);
            }
            for (i = 0; i < k - 1; i++) {
                printf("'%c' ", set[i]);
            }
            printf("'%c'\n", set[k - 1]);
        }
    }
}
