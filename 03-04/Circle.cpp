#include "Circle.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>

Circle::Circle(float radius) : radius_(radius) {}

Circle::~Circle() {}

void Circle::Size() {
  area_ = std::powf(radius_, 2.0f) * static_cast<float>(M_PI);
}

void Circle::Draw() { printf(u8"Circle area: %f\n\n", area_); }