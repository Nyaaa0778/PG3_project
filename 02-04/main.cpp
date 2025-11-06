#include <Windows.h>
#include <stdio.h>
#include <time.h>

void DelayReveal(void (*Fn)(int, int), unsigned int delayMs, int roll,
                 int userGuess) {
  Sleep(delayMs);
  Fn(roll, userGuess);
}

int main(void) {

  SetConsoleOutputCP(65001);

  // 乱数初期化
  srand((unsigned)time(NULL));

  // 0で偶数、1で奇数
  int userGuess = 0;
  printf(u8"偶数なら0、奇数なら1を入力してください: ");
  scanf_s(u8"%d", &userGuess);

  // サイコロを振る
  int roll = rand() % 6 + 1;

  // 3秒待ってから結果表示
  DelayReveal(
      [](int roll, int userGuess) {
        // 出目の表示
        printf(u8"出目は %d でした。\n", roll);

        // 偶数なら0、奇数なら1
        int rollParity = roll % 2;

        // 正解か不正解かの判定
        if ((userGuess == 1 && rollParity == 1) ||
            (userGuess == 0 && rollParity == 0)) {
          printf(u8"正解\n");
        } else {
          printf(u8"不正解\n");
        }
      },
      3000, roll, userGuess);

  return 0;
}