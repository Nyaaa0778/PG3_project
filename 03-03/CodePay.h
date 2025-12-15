#pragma once
#include "Pay.h"

class CodePay : public Pay {
public:
  // コンストラクタ
  CodePay();

  // デストラクタ
  ~CodePay();

  /// <summary>
  /// 支払い
  /// </summary>
  /// <param name="amount">金額</param>
  void Update(int amount) override;
};