#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        fprintf(stdout, "%s\n", argv[i]);
    }
    return 0;
}
