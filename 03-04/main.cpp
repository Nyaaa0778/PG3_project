#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI
#define _USE_MATH_DEFINES
#include <Windows.h>
#include <cmath>
#include <stdio.h>

//====================================
// 基底クラス
//====================================
class IShape {
public:
  virtual ~IShape() {}
  virtual void Size() = 0; // 面積計算
  virtual void Draw() = 0; // 描画
};

//====================================
// 円クラス
//====================================
class Circle : public IShape {
public:
  Circle(float radius) : radius_(radius) {}

  void Size() override { area_ = radius_ * radius_ * static_cast<float>(M_PI); }

  void Draw() override {
    printf(u8"Circle\n");
    printf(u8" radius = %.2f\n", radius_);
    printf(u8" area   = %.2f\n\n", area_);
  }

private:
  float radius_ = 0.0f;
  float area_ = 0.0f;
};

//====================================
// 矩形クラス
//====================================
class Rectangle : public IShape {
public:
  Rectangle(float width, float height) : width_(width), height_(height) {}

  void Size() override { area_ = width_ * height_; }

  void Draw() override {
    printf(u8"Rectangle\n");
    printf(u8" width  = %.2f\n", width_);
    printf(u8" height = %.2f\n", height_);
    printf(u8" area   = %.2f\n\n", area_);
  }

private:
  float width_ = 0.0f;
  float height_ = 0.0f;
  float area_ = 0.0f;
};
int main(void) {

  SetConsoleOutputCP(65001);

  IShape *iShape[2];

  float radius = 3.0f;

  float width = 5.0f;
  float height = 4.0f;

  for (int i = 0; i < 2; i++) {
    if (i < 1) {
      iShape[i] = new Circle(radius);
    } else {
      iShape[i] = new Rectangle(width, height);
    }

    iShape[i]->Size();

    iShape[i]->Draw();
  }

  for (int i = 0; i < 2; i++) {
    delete iShape[i];
  }

  return 0;
}