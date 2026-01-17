#include <Windows.h>
#include <condition_variable>
#include <mutex>
#include <stdio.h>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
int turn = 1; // thread1から

void Print(int id) {
  std::unique_lock<std::mutex> lock(mtx);

  // 自分の番になるまで待つ
  cv.wait(lock, [&] { return turn == id; });

  printf("thread %d\n", id);

  // 次の番へ
  ++turn;
  cv.notify_all();
}

int main() {
  SetConsoleOutputCP(65001);

  std::thread t1(Print, 1);
  std::thread t2(Print, 2);
  std::thread t3(Print, 3);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
