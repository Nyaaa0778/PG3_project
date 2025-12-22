#pragma once
class IShape {
public:
  // コンストラクタ
  IShape() = default;

  // 仮想デストラクタ
  virtual ~IShape() = default;

  virtual void Size() = 0;
  virtual void Draw() = 0;
};
