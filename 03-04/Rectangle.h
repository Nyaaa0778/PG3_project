#pragma once
#include "IShape.h"

class Rectangle : public IShape {
public:
  // コンストラクタ
  Rectangle(float width, float height);

  // デストラクタ
  ~Rectangle();

  // 面積を求める
  void Size() override;
  // 描画
  void Draw() override;

private:
  float width_ = 0.0f;
  float height_ = 0.0f;
  float area_ = 0.0f;
};
