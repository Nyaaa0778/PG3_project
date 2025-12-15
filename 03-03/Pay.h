#pragma once

class Pay {
public:
  // コンストラクタ
  Pay() = default;

  // 仮想デストラクタ
  virtual ~Pay() = default;

  /// <summary>
  /// 支払い
  /// </summary>
  /// <param name="amount">金額</param>
  virtual void Update(int amount) = 0;
};
