#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define FOREACH_KEY(KEY)	\
		KEY(b)              \
		KEY(Kb)             \
		KEY(Mb)             \
		KEY(Gb)             \
		KEY(Tb)

#define GEN_ENUM(ENUM) ENUM,
#define GEN_STRING(STRING) #STRING,

enum sizes_e{
    FOREACH_KEY(GEN_ENUM)
};

const char *sizes_s[] = {
    FOREACH_KEY(GEN_STRING)
};

void
humanize(long long int size) {
    double hsize = size;
    int postfix = 0;
    while (hsize > 1024) {
        hsize /= 1024;
        postfix++;
    }
    printf("%.2lf%s\n", hsize, sizes_s[postfix]);
}

#define LEN 2048

int main() {
    if (!isatty(fileno(stdin))) {
        char *buff = (char*)malloc(LEN);
        memset(buff, 0, LEN);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            long long int num = strtol(buff, NULL, 10);
            humanize(num);
        }
    }
    return 0;
}
