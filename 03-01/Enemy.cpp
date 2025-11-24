#include "Enemy.h"
#include <stdio.h>

void Enemy::Update() {
  // 現在フェーズの関数を実行
  (this->*stateTable_[static_cast<size_t>(phase_)])();
}

// メンバ関数ポインタのテーブル
void (Enemy::*Enemy::stateTable_[])() = {
    &Enemy::StateApproach, &Enemy::StateAttack, &Enemy::StateLeave};

// 接近
void Enemy::StateApproach() {
  printf(u8"接近中...\n");
  phase_ = Phase::Attack;
}
// 攻撃
void Enemy::StateAttack() {
  printf(u8"攻撃中...\n");
  phase_ = Phase::Leave;
}
// 離脱
void Enemy::StateLeave() {
  printf(u8"離脱中...\n");

  // 離脱したら終了
  isEnd_ = true;
}