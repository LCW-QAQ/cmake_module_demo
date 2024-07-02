#include <bits/stdc++.h>
#include <cmkmod.h>

class A {
public:
  A() { std::printf("A ctor\n"); }
  A(const A &a) { std::printf("A copy ctor\n"); }
  A(A &&a) { std::printf("A move ctor\n"); }
};

int main() {
  say_hello();
  std::vector<A> vec;
  // A a;
  // vec.push_back(A{});
  vec.emplace_back();
  return 0;
}