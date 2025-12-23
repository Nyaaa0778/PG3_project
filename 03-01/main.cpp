#include <Windows.h>
#include <chrono>
#include <stdio.h>
#include <thread>

class Enemy {
public:
  Enemy() {
    // 初期状態
    state_ = &Enemy::Approach;
  }

  void Update() {
    // 現在の状態関数を実行
    (this->*state_)();
  }

  bool IsEnd() const { return isEnd_; }

private:
  // 接近
  void Approach() {
    std::printf(u8"接近中...\n");
    // 次の状態へ
    state_ = &Enemy::Attack;
  }

  // 射撃
  void Attack() {
    std::printf(u8"射撃中...\n");
    // 次の状態へ
    state_ = &Enemy::Leave;
  }

  // 離脱
  void Leave() {
    std::printf(u8"離脱中...\n");
    // 終了
    isEnd_ = true;
  }

private:
  void (Enemy::*state_)() = nullptr;
  bool isEnd_ = false;
};

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