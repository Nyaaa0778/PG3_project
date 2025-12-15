#pragma once
#include "Pay.h"

class CashPay : public Pay {
public:
  // コンストラクタ
  CashPay();

  // デストラクタ
  ~CashPay();

  /// <summary>
  /// 支払い
  /// </summary>
  /// <param name="amount">金額</param>
  void Update(int amount) override;
};
