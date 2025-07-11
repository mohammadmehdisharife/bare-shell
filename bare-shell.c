#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char command[100];
  char *args[10];
  char *token;
  int i;

  while (1) {
    printf("-> ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';

    if (strcmp(command, "exit") == 0) {
      exit(0);
    }

    i = 0;
    token = strtok(command, " ");
    while (token != NULL && i < 9) {
      args[i++] = token;
      token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (fork() == 0) {
      execvp(args[0], args);
      perror("run");
      return 1;
    }
    wait(NULL);
  }
  return 0;
}
