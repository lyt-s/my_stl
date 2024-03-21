#include <stdio.h>
#include <unistd.h>

#include "stdlib.h"

// 不能放在这里  放在这里  会对malloc_hook 和 free_hook
// 内部实际调用的也替换，就形成的递归调用了 并且无法规避 #define malloc(size)
// malloc_hook(size, __FILE__, __LINE__) #define free(p) 		free_hook(p,
// __FILE__, __LINE__)
extern "C" {

#define MEM_FILE_LENGTH 40
// 实现目标函数
void *malloc_hook(size_t size, const char *file, int line) {
  // 这里还是通过文件的方式进行识别
  void *ptr = malloc(size);
  char file_name_buff[MEM_FILE_LENGTH] = {0};
  sprintf(file_name_buff, "./mem/%p.mem", ptr);

  // 打开文件写入必要信息 使用前创建目录级别
  FILE *fp = fopen(file_name_buff, "w");
  fprintf(fp, "[file:%s  line:%d ] ---->mem:%p  size:%lu \n", file, line, ptr,
          size);
  fflush(fp);  // 刷新写入文件

  printf("exec malloc [%p:%lu], file: %s, line:%d \n", ptr, size, file, line);
  return ptr;
}

void free_hook(void *p, const char *file, int line) {
  char file_name_buff[MEM_FILE_LENGTH] = {0};
  sprintf(file_name_buff, "./mem/%p.mem", p);

  if (unlink(file_name_buff) < 0) {
    printf("double free: %p, file: %s. line :%d \n", p, file, line);
  }

  // 这里的打印实际就没意义了
  printf("exec free [%p], file: %s line:%d \n", p, file, line);
  free(p);
}
// 宏定义实现代码中调用malloc/free时调用我们目标函数
#define malloc(size) malloc_hook(size, __FILE__, __LINE__)
#define free(p) free_hook(p, __FILE__, __LINE__)
}

int main() {
  // init_malloc_free_hook(); //执行一次
  void *ptr1 = malloc(10);
  void *ptr2 = malloc(20);

  free(ptr1);

  void *ptr3 = malloc(30);
  free(ptr3);
  return 0;
}