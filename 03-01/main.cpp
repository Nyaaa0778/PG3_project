#include "Enemy.h"
#include <Windows.h>
#include <thread>

int main(void) {

  SetConsoleOutputCP(65001);

  Enemy enemy;

  while (!enemy.IsEnd()) {
    // 更新
    enemy.Update();

    // フェーズ切り替えの間
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  return 0;
}