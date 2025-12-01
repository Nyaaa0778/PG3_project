#pragma once

template <typename Type1, typename Type2>

class Comparator {
private:
  Type1 a_;
  Type2 b_;

public:
  Comparator(Type1 a, Type2 b) : a_(a), b_(b) {}

  auto Min() { return (a_ < b_) ? a_ : b_; }
};
