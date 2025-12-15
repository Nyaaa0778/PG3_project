#pragma once
#include "Pay.h"

class CardPay : public Pay {
public:
  // コンストラクタ
  CardPay();

  // デストラクタ
  ~CardPay();

  /// <summary>
  /// 支払い
  /// </summary>
  /// <param name="amount">金額</param>
  void Update(int amount) override;
};
