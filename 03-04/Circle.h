#pragma once
#include "IShape.h"

class Circle : public IShape {
public:
  // コンストラクタ
  Circle(float radius);

  // デストラクタ
  ~Circle();

  // 面積を求める
  void Size() override;
  // 描画
  void Draw() override;

private:
  float radius_ = 0.0f;
  float area_ = 0.0f;
};
