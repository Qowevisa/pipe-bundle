#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINE_CAP 2048

char *reverse(char *p) {
    char *ancor = p;
    char copy[LINE_CAP + 1];
    memset(copy, 0, LINE_CAP+1);
    strncat(copy, p, LINE_CAP);
    size_t pos = strlen(p) - 2;
    while (*p != '\n') {
        *p = copy[pos];
        pos--;
        p++;
    }
    return ancor;
}

int main() {
    if (!isatty(fileno(stdin))) {
        char *buf = malloc(LINE_CAP);
        size_t n = LINE_CAP;
        while (getline(&buf, &n, stdin) != -1) {
            printf("%s", reverse(buf));
        }
    }
    return 0;
}
