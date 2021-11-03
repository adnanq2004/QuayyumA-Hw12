#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {

  struct dirent* point;
  struct stat* info;
  int total = 0;

  char dir[100];
  if (argc  > 1) {
    strcpy(dir, argv[1]);
  }
  else {
    printf("please provide a proper directory\n");
    scanf("%s",dir);
    if (opendir(dir) < 0) {
      printf("Error %d: %s\n", errno, strerror(errno));
      return 0;
    }
  }

  printf("statistics for directory: %s\n\n", dir);

  DIR * direct1 = opendir(dir);
  printf("directories:\n");
  point = readdir(direct1);
  while (point && point->d_type == DT_DIR) {
    info = malloc(sizeof(struct stat));
    stat(point->d_name, info);
    total += info->st_size;
    printf("           %s\n", point->d_name);
    point = readdir(direct1);
  }
  closedir(direct1);
  printf("\n");

  DIR * direct2 = opendir(dir);
  printf("regular files:\n");
  point = readdir(direct2);
  while (point && point->d_type == DT_REG) {
    info = malloc(sizeof(struct stat));
    stat(point->d_name, info);
    total += info->st_size;
    printf("           %s\n", point->d_name);
    point = readdir(direct2);
  }
  closedir(direct2);
  printf("\n");

  DIR * direct3 = opendir(dir);
  printf("other files files:\n");
  point = readdir(direct3);
  while (point && point->d_type != DT_REG && point->d_type != DT_DIR) {
    info = malloc(sizeof(struct stat));
    stat(point->d_name, info);
    total += info->st_size;
    printf("           %s\n", point->d_name);
    point = readdir(direct3);
  }
  closedir(direct3);
  printf("\n");

  printf("total size: %d\n", total);

  return 0;

}
