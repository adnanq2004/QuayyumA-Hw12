#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

  struct dirent* point;
  struct stat* info;
  int total = 0;
  printf("statistics for directory: ./\n\n");

  DIR * direct1 = opendir("./");
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

  DIR * direct2 = opendir("./");
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

  DIR * direct3 = opendir("./");
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
