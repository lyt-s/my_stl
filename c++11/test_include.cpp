#include "string.h"

int main() {
  char str = 'a';
  char *s = new char;
  strcpy(s, &str);
  return 0;
}