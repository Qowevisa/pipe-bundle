#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    unsigned char counter = 2;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i],"e") == 0 || strcmp(argv[i],"even") == 0) {
            counter = 1;
        } else if (strcmp(argv[i],"o") == 0 || strcmp(argv[i],"odd") == 0) {
            counter = 2;
        } else if (strcmp(argv[i],"--help") == 0 || strcmp(argv[i],"-h") == 0) {
            fprintf(stdout, 
                "lines: reads stdin and prints only odds or evens lines\n"
                "Usage: lines [odd(o)|even(e)]\n"
                "Note: if none additional arguments was given,\n"
                "  it will automaticaly prints only even lines\n");
            return 0;
        }
    }
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            if (counter == 2) {
                fprintf(stdout, "%s", buff);
                counter = 0;
            }
            counter++;
        }
    }
    return 0;
}
