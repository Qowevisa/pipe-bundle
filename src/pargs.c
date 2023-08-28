#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <command> [command arguments...]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  char command[1024] = "";
  for (int i = 1; i < argc; i++) {
    strcat(command, argv[i]);
    strcat(command, " ");
  }

  char line[256];
  while (fgets(line, sizeof(line), stdin)) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }
    char final_command[1280];
    snprintf(final_command, sizeof(final_command), "%s%s", command, line);
    system(final_command);
  }

  return 0;
}
