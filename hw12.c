#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

  DIR * direct = opendir("./");
  struct dirent* point;
  struct stat* info;
  point = readdir(direct);
  int total = 0;
  printf("statistics for directory: .\n");
  while (point) {
    printf("%s ", point->d_name);
    info = malloc(sizeof(struct stat));
    stat(point->d_name, info);
    if (point->d_type == DT_REG) {
      total += info->st_size;
      printf("is regular file\n\n");
    }
    else if (point->d_type == DT_DIR) {
      printf("is directory\n\n");
    }
    else {
      printf("is other file\n\n");
    }
    free(info);
    point = readdir(direct);
  }
  printf("total size: %d\n", total);

}
