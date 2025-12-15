#include <Windows.h>
#include <stdio.h>

#include "CardPay.h"
#include "CashPay.h"
#include "CodePay.h"
#include "Pay.h"

int main(void) {

  SetConsoleOutputCP(65001);

  // 支払い方法
  Pay *paymentMethods[3] = {
      new CashPay(),
      new CardPay(),
      new CodePay(),
  };

  // 支払い
  for (int i = 0; i < 3; i++) {
    paymentMethods[i]->Update(200);
  }

  // 解放
  for (int i = 0; i < 3; i++) {
    delete paymentMethods[i];
  }

  return 0;
}