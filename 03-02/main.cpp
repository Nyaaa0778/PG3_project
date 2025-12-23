#include <Windows.h>
#include <stdio.h>

template <typename Type1, typename Type2>

class Comparator {
private:
  Type1 a_;
  Type2 b_;

public:
  Comparator(Type1 a, Type2 b) : a_(a), b_(b) {}

  auto Min() { return (a_ < b_) ? a_ : b_; }
};

int main(void) {

  SetConsoleOutputCP(65001);

  Comparator<int, int> intAndInt(10, 30);
  Comparator<int, float> intAndFloat(1, 7.0f);
  Comparator<int, double> intAndDouble(100, 32.0);
  Comparator<float, float> floatAndFloat(64.0f, 16.0f);
  Comparator<float, double> floatAndDouble(128.0f, 256.0);
  Comparator<double, double> doubleAndDouble(12.0, 34.0);

  // 小さい方を表示
  printf(u8"int    & int     Min = %d\n", intAndInt.Min());
  printf(u8"int    & float   Min = %f\n", intAndFloat.Min());
  printf(u8"int    & double  Min = %f\n", intAndDouble.Min());
  printf(u8"float  & float   Min = %f\n", floatAndFloat.Min());
  printf(u8"float  & double  Min = %f\n", floatAndDouble.Min());
  printf(u8"double & double  Min = %f\n", doubleAndDouble.Min());

  return 0;
}