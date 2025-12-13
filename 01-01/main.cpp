#include <Windows.h>
#include <cstring>
#include <iostream>
#include <list>

int main() {

  SetConsoleOutputCP(65001);

  // 駅名
  std::list<const char *> station{
      "Tokyo",        "Kanda",     "Akihabara", "Okachimachi",  "Ueno",
      "Uguisudani",   "Nippori",   "Tabata",    "Komagome",     "Sugamo",
      "Otsuka",       "Ikebukuro", "Mejiro",    "Takadanobaba", "Shin-Okubo",
      "Shinjuku",     "Yoyogi",    "Harajuku",  "Shibuya",      "Ebisu",
      "Meguro",       "Gotanda",   "Osaki",     "Shinagawa",    "Tamachi",
      "Hamamatsucho", "Shimbashi", "Yurakucho"};

  // 昭和3年
  std::cout << u8"昭和3年" << "\n\n";

  for (std::list<const char *>::iterator itr = station.begin();
       itr != station.end(); ++itr) {
    std::cout << "[" << *itr << "]\n";
  }

  // 昭和47年
  std::cout << "\n\n" << u8"昭和47年" << "\n\n";

  for (std::list<const char *>::iterator itr = station.begin();
       itr != station.end(); ++itr) {

    // 西日暮里を追加
    if (std::strcmp(*itr, "Tabata") == 0) {
      itr = station.insert(itr, "Nishi-Nippori");
      break;
    }
  }

  for (std::list<const char *>::iterator itr = station.begin();
       itr != station.end(); ++itr) {
    std::cout << "[" << *itr << "]\n";
  }

  // 令和5年
  std::cout << "\n\n" << u8"令和5年" << "\n\n";

  for (std::list<const char *>::iterator itr = station.begin();
       itr != station.end(); ++itr) {

    if (std::strcmp(*itr, "Tamachi") == 0) {
      itr = station.insert(itr, "Takanawa Gateway");
      break;
    }
  }

  for (std::list<const char *>::iterator itr = station.begin();
       itr != station.end(); ++itr) {
    std::cout << "[" << *itr << "]\n";
  }

  return 0;
}