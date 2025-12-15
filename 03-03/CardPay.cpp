#include "CardPay.h"
#include <stdio.h>

CardPay::CardPay() {}

CardPay::~CardPay() {}

/// <summary>
/// 支払い
/// </summary>
/// <param name="amount">金額</param>
void CardPay::Update(int amount) { printf(u8"カード払い\n\n"); }
