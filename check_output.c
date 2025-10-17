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

  char **files = malloc(sizeof(char *) * num_files);

  size_t i = 0;
  while (de = readdir(test_dir)) {

    if ((strcmp(de->d_name, "..") != 0) && (strcmp(de->d_name, ".") != 0)) {
      files[i] = malloc(strlen(de->d_name) + 1);
      files[i] = de->d_name;
      i++;
    }
  }

  printf("file 0 = %s\n", files[0]);

  char *lineptr = NULL;
  ssize_t check = 0;

  relative_path =
      realloc(relative_path, sizeof(relative_path) + sizeof(files[i]) + 1);
  strcat(relative_path, files[0]);
  printf("\n\n\n%s\n", relative_path);

  FILE *file_stream = fopen(relative_path, "r");
  if (file_stream == NULL) {
    printf("allocation error\n");
    return  1;
  }

  size_t len = 0;
  while ((check = getline(&lineptr, &len, file_stream)) != -1) {
    printf("%s", lineptr);
  }

  fclose(file_stream);

  // free(files);
  closedir(test_dir);
  free(relative_path);

  return 0;
}
