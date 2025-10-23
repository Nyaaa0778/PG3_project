#include <Windows.h>
#include <iostream>

int Recursive(int salary, int time) {
  if (time <= 0) {
    return 0;
  }

  if (time == 1) {
    return salary;
  }

  return salary + Recursive(salary * 2 - 50, time - 1);
}

int main() {

  SetConsoleOutputCP(65001);

  //一般的な賃金体系の給料
  const int normalSalary = 1226;
  //再帰的な賃金体系の給料
  const int startSalary = 100;

  for (int hour = 1; hour <= 10; ++hour) {
    int normalTotalSalary = normalSalary * hour;
    int recursiveTotalSalary = Recursive(startSalary, hour);

    printf(u8"%2d時間働くと\n通常: %6d円, 再帰的: %8d円", hour,
           normalTotalSalary, recursiveTotalSalary);

    if (normalTotalSalary <= recursiveTotalSalary) {
      printf(u8"\n\n%2d時間で再帰的な賃金体系の給料の方が高くなる\n", hour);

      break;
    } else {
      printf(u8"\n");
    }
  }

  return 0;
}