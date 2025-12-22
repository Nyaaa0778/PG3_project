#include "Rectangle.h"
#include <stdio.h>

Rectangle::Rectangle(float width, float height)
    : width_(width), height_(height) {}

Rectangle::~Rectangle() {}

void Rectangle::Size() { area_ = width_ * height_; }

void Rectangle::Draw() { printf("Rectangle area: %f\n\n", area_); }
