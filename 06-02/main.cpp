#include <Windows.h>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
bool loaded = false;
std::vector<std::vector<int>> mapData;

// マップチップの数値を表示用の1文字に変換する関数
char ToChar(int v) {
  if (v == 0)
    return '.';
  if (v == 1)
    return '#';
  if (v == 2)
    return 'P';
  if (v == 3)
    return 'O';
  return '?';
}

// CSVの読み込み
void LoadCsv(const std::string &path) {
  std::vector<std::vector<int>> local;

  std::ifstream ifs(path);
  std::string line;
  while (std::getline(ifs, line)) {
    std::vector<int> row;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
      row.push_back(cell.empty() ? 0 : std::stoi(cell));
    }
    if (!row.empty())
      local.push_back(std::move(row));
  }

  {
    std::lock_guard<std::mutex> lock(mtx);
    mapData = std::move(local);
    loaded = true;
  }
  cv.notify_one();
}

int main() {
  SetConsoleOutputCP(65001);

  std::thread t(LoadCsv, "map.csv");

  { // 読み込み完了待ち
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return loaded; });
  }

  // マップ表示
  for (auto &row : mapData) {
    for (int v : row)
      std::cout << ToChar(v);
    std::cout << "\n";
  }

  t.join();
  return 0;
}
