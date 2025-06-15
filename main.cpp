#include <print>
#include "hello.h"

using std::println;

int main() {
  sayHello();

#ifdef DEBUG_MODE
  println("Hello World from Debug mode!");
#else
  println("Hello World from Release mode!");
#endif

  return 0;
}
