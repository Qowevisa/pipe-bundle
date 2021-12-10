#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	if (!isatty(fileno(stdin))) {
		char *buff = NULL;
		size_t n = 0;
		size_t buff_size = getline(&buff, &n, stdin);
		while (buff_size != -1) {
			// getting the name without '\n' char
			char *nof = (char*)malloc(buff_size - 1);
			for (int i = 0; i < buff_size - 1; i++)
				nof[i] = buff[i];

			pid_t id = fork();
			// Child process ID
			if (id == 0) {
				char *args[] = {"rm", nof, NULL};
				int val = execvp(args[0], args);
				if (val == -1) {
					printf("Error occured in execvp!\n");
					exit(2);
				}
				// if for some reasons it won't end by calling execvp.
				return 0;
			}
			buff_size = getline(&buff, &n, stdin);
		}
	}
	return 0;
}
