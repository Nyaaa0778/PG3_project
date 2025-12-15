#include "CodePay.h"
#include <stdio.h>

CodePay::CodePay() {}

CodePay::~CodePay() {}

/// <summary>
/// 支払い
/// </summary>
/// <param name="amount">金額</param>
void CodePay::Update(int amount) { printf(u8"コード決済\n\n"); }
