#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	if (!isatty(fileno(stdin))) {
		char *buff = (char*)calloc(2048, 1);
		size_t n = 0;
		while (getline(&buff, &n, stdin) != -1) {
			// getting the name without '\n' char
			char *nof = (char*)calloc(2048, 1);
            size_t i = 0;
            while (buff[i] != '\n') {
                nof[i] = buff[i];
                i++;
            }

			pid_t id = fork();
			// Child process ID
			if (id == 0) {
				char *args[] = {"rm", nof, NULL};
				int val = execvp(args[0], args);
				if (val == -1) {
					printf("Error occured in execvp!\n");
					return 2;
				}
				// if for some reasons it won't end by calling execvp.
				return 0;
			}
		}
	}
	return 0;
}
