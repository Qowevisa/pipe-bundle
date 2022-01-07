#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <C>\n", argv[0]);
        return 1;
    }
    if (!isatty(fileno(stdin))) {
        char c;
        while ((c = fgetc(stdin)) != EOF) {
            if (c == argv[1][0]) {
                fputc('\n', stdout);
            } else {
                fputc(c, stdout);
            }
        }
    }
    return 0;
}
