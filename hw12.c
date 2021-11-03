#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {

  struct dirent* point;
  struct stat* info;
  int total = 0;
  char * dir = NULL;

  if (argc == 2) {
    dir = argv[1];
    // strcpy(dir,argv[1]);
  }
  else if (argc > 2) {
    printf("too many inputs, please provide fewer inputs");
  }
  else {
    while (!dir) {
      // scanf("please provide a valid directory: %s\n", dir);
      // if (!dir) {
      //   int errnum = errno;
      //   // printf("there was an error:\n%s\n", perror(errno));
      //   perror("there was an error");
      // }
      // dir = "./";
      scanf("%s\n", dir);
      // if (!dir) {
        // printf("there was an error: %s\n", strerror(errno));
        // int errnum = errno;
        // perror(errnum);
        // printf("there was an error:\n\n%s\n\n", errlang);
      // }
    }
  }

  printf("statistics for directory: %s\n\n", dir);

  DIR * direct1 = opendir(dir);
  printf("directories\n\n");
  point = readdir(direct1);
  while (point && point->d_type == DT_DIR) {
    info = malloc(sizeof(struct stat));
    stat(point->d_name, info);
    total += info->st_size;
    printf("%s\n", point->d_name);
    point = readdir(direct1);
  }
  closedir(direct1);
  printf("\n");

  DIR * direct2 = opendir(dir);
  printf("regular files\n");
  point = readdir(direct2);
  while (point && point->d_type == DT_REG) {
    info = malloc(sizeof(struct stat));
    stat(point->d_name, info);
    total += info->st_size;
    printf("%s\n", point->d_name);
    point = readdir(direct2);
  }
  closedir(direct2);
  printf("\n");

  DIR * direct3 = opendir(dir);
  printf("other files files\n");
  point = readdir(direct3);
  while (point && point->d_type != DT_REG && point->d_type != DT_DIR) {
    info = malloc(sizeof(struct stat));
    stat(point->d_name, info);
    total += info->st_size;
    printf("%s\n", point->d_name);
    point = readdir(direct3);
  }
  closedir(direct3);
  printf("\n");

  printf("total size: %d\n", total);

  return 0;

}
