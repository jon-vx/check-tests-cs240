#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  if (argc < 4) {
    printf("usage: ./check_output.c <prgm.c> <tests dir> <num_tests> \n");
    return 1;
  }

  printf("starting script...\n");

  char *file = argv[1];
  char *dir = argv[2];
  int num_files = atoi(argv[3]);

  size_t dir_length = strlen(dir);
  char *relative_path = malloc(dir_length + 2);

  if (relative_path == NULL) {
    perror("malloc");
    return 1;
  }

  strcpy(relative_path, dir);
  if (dir[dir_length - 1] != '/') {
    strcat(relative_path, "/");
  }

  printf("file: %s\ndir: %s\n", file, relative_path);

  struct dirent *de;

  DIR *test_dir = opendir(relative_path);

  char **files = malloc(sizeof(FILE *) * num_files);

  size_t i = 0;
  char buffer[30];
  while (de = readdir(test_dir)) {

    if ((strcmp(de->d_name, "..") != 0) && (strcmp(de->d_name, ".") != 0)) {
      strcpy(buffer, relative_path);
      strcat(buffer, de->d_name);

      files[i] = malloc(sizeof(buffer) + 1);
      strcpy(files[i], buffer);

      memset(buffer, '\0', 30);
      i++;
    }
  }

  for (int i = 0; i < num_files; i++) {

    printf("\n-------------------------------------------\n");

    FILE *current_file = fopen(files[i], "r");

    ssize_t check = 0;
    char *lineptr = NULL;
    size_t len = 0;
    while ((check = getline(&lineptr, &len, current_file)) != -1) {
      printf("%s", lineptr);
    }

    fclose(current_file);
  }

  printf("\n-------------------------------------------\n");
  // free(files);
  closedir(test_dir);

  return 0;
}
