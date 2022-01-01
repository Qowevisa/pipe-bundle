#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // reading from stdin
    if (!isatty(fileno(stdin))) {
        //
        long long sum = 0;
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            sum += atoi(buff);
        }
        //
        printf("%lld\n", sum);
    }
    return 0;
}
