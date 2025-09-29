#include <Windows.h>
#include <iostream>

int main() {

  SetConsoleOutputCP(65001);

  char string[] = u8"あいうえお\nアイウエオ";

  // 文字列を表示
  printf("%s", string);

  return 0;
}