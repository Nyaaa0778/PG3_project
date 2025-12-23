#include <Windows.h>
#include <stdio.h>

//====================================
// 支払い基底クラス
//====================================
class Pay {
public:
  virtual ~Pay() {} // 仮想デストラクタ
  virtual void Update(int money) = 0;
};

//====================================
// 現金払い
//====================================
class CashPay : public Pay {
public:
  void Update(int money) override {
    printf(u8"現金で %d 円支払いました\n", money);
  }
};

//====================================
// カード払い
//====================================
class CardPay : public Pay {
public:
  void Update(int money) override {
    printf(u8"カードで %d 円支払いました\n", money);
  }
};

//====================================
// コード決済
//====================================
class CodePay : public Pay {
public:
  void Update(int money) override {
    printf(u8"コード決済で %d 円支払いました\n", money);
  }
};

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