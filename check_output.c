#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("usage: ./check_output.c <file.c> <tests dir>\n");
    return 1;
  }

  printf("starting script...\n");

  char *file = argv[1];
  char *dir = argv[2];

  printf("file: %s\ndir: %s\n", file, dir);

  struct dirent *de;

  DIR *test_dir = opendir(dir);

  while (de = readdir(test_dir)) {

    if ((strcmp(de->d_name, "..") != 0) && (strcmp(de->d_name, ".") != 0)) {
      printf("%s\n", de->d_name);
    }
  }

  closedir(test_dir);

  return 0;
}
