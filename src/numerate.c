#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    size_t counter = 0;
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            printf("%ld:%s", counter++, buff);
        }
    }
    return 0;
}
