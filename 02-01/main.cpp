#include <Windows.h>
#include <iostream>

template <typename Type> Type Min(Type a, Type b) {
  if (a > b) {
    return b;
  } else {
    return a;
  }
}

int main() {

  SetConsoleOutputCP(65001);

  // char string[] = u8"あいうえお\nアイウエオ";

  //// 文字列を表示
  // printf("%s", string);

  printf("%d\n", Min<int>(114, 514));
  printf("%f\n", Min<float>(11.4f, 51.4f));
  printf("%f\n", Min<double>(11.4333333, 51.4));

  return 0;
}