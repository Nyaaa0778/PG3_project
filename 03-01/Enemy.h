#pragma once

class Enemy {
public:
  enum class Phase {
    Approach, // 接近
    Attack,   // 射撃
    Leave     // 離脱
  };

public:
  // 更新
  void Update();

  // 終了フラグのGetter
  bool IsEnd() const { return isEnd_; }

private:
  // フェーズ
  Phase phase_ = Phase::Approach;

  // 離脱したら終了
  bool isEnd_ = false;

private:
  // メンバ関数ポインタのテーブル
  static void (Enemy::*stateTable_[])();

  // 接近
  void StateApproach();
  // 攻撃
  void StateAttack();
  // 離脱
  void StateLeave();
};
