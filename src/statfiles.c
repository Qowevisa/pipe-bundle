#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

enum states {
    silent   = 1 << 0,
    only_all = 1 << 1,
    human    = 1 << 2
};

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

static inline void print_args(int state, const char *str, long long int size) {
    if (!(state & only_all)) {
        if (!(state & silent)) {
            printf("%s : ", str);
        }
        if (state & human) {
            double hsize = size;
            int postfix = 0;
            while (hsize > 1024) {
                hsize /= 1024;
                postfix++;
            }
            printf("%.2lf%s\n", hsize, sizes_s[postfix]);
        } else {
            printf("%lld\n", size);
        }
    }
}

#define validate(str)                                                   \
    if (stat(str, &buffer) != 0) {                                      \
        fprintf(stderr, "%s: %s: %s\n", argv[0], str, strerror(errno)); \
        continue;                                                       \
    }                                                                   \
    if (!S_ISREG(buffer.st_mode)) {                                     \
        continue;                                                       \
    }                                                                   

int main(int argc, char *argv[]) {
    // getting opts
    int state = 0;
    for (int i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            int j = 0;
            char c;
            while ((c = argv[i][j]) != '\0') {
                switch (c) {
                    case 's':
                        state |= silent;
                        break;
                    case 'a':
                        state |= only_all;
                        break;
                    case 'h':
                        state |= human;
                        break;
                }
                j++;
            }
        }
    }
    //
    long long all_size = 0;
    struct stat buffer;
    // reading from stdin
    if (!isatty(fileno(stdin))) {
        //
        char *buff = (char*)malloc(2048);
        size_t n;
        while (getline(&buff, &n, stdin) != -1) {
            // removing \n in buff
            buff[strlen(buff) - 1] = '\0';
            // validating
            validate(buff);
            //
            print_args(state, buff, buffer.st_size);
            all_size += buffer.st_size;
        }
    }
    for (int i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            continue;
        }
        // validating
        validate(argv[i]);
        //
        print_args(state, argv[i], buffer.st_size);
        all_size += buffer.st_size;
    }
    //
    print_args(state ^ only_all, "all", all_size);
    return 0;
}
