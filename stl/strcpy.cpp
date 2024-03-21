#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>

char* Mystrcpy(char* dest, const char* src) {
  char* ret = dest;
  assert(dest != NULL);
  assert(src != NULL);
  while (*src != '\0') {
    *(dest++) = *(src++);
  }
  *dest = '\0';
  return ret;
}

// 把 src 所指向的字符串追加到 dest 所指向的字符串的结尾。
char* MyStrcat(char* dest, const char* src) {
  char* ret = dest;
  assert(dest != NULL);
  assert(src != NULL);
  while (*dest != '\0') {
    dest++;
  }
  while (*src != '\0') {
    *(dest++) = *src++;
  }
  *dest = '\0';
  return ret;
}

// 把 str1 所指向的字符串和 str2 所指向的字符串进⾏⽐较。
// 该函数返回值如下：
// 如果返回值 < 0，则表示 str1 ⼩于 str2。
// 如果返回值 > 0，则表示 str1 ⼤于 str2。
// 如果返回值 = 0，则表示 str1 等于 str2

int my_strcmp(const char* s1, const char* s2) {
  assert(s1 != NULL);
  assert(s2 != NULL);
  while (*s1 != '\0' && *s2 != '\0') {
    if ((*s1) > (*s2)) {
      return 1;
    } else if (*s1 < *s2) {
      return -1;
    } else {
      s1++;
      s2++;
    }
  }

  if (*s1 > *s2) {
    return 1;
  } else if (*s1 < *s2) {
    return -1;
  } else {
    return 0;
  }
}

// 在字符串 str1 中查找第⼀次出现字符串 str2 的位置，不包含终⽌符 '\0'
char* my_strstr(char* str1, char* str2) {
  char* s = str1;
  assert(*str1 != '\0');
  assert(*str2 != '\0');
  if (*str2 == '\0') {
    return nullptr;
  }
  while (*s != '\0') {
    char* s1 = s;
    char* s2 = str2;
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
      s1++;
      s2++;
    }
    if (*s2 == '\0') {
      return str2;
    }
    if (*s2 != '\0' && *s1 == '\0') {
      return NULL;
    }
    s++;
  }
  return NULL;
}

void* my_memcpy(void* dest, void* src, size_t num) {
  void* ret = dest;
  size_t i = 0;
  assert(dest != NULL);
  assert(src != NULL);
  for (i = 0; i < num; i++) {
    *(char*)dest = *(char*)src;
    dest = (char*)dest + 1;
    src = (char*)src + 1;
  }
  return ret;
}

int main() {
  char src[40];
  char dest[100];
  memset(dest, '\0', sizeof(dest));
  Mystrcpy(src, "this is a test");
  Mystrcpy(dest, src);
  std::cout << my_strcmp(dest, src) << "\n";
  MyStrcat(dest, src);

  printf("最终目标字符串：%s\n", dest);
  return 0;
}