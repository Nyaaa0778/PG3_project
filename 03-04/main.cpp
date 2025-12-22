#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI
#include <Windows.h>

#include "Circle.h"
#include "IShape.h"
#include "Rectangle.h"

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