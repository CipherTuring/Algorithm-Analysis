#include <iostream>

int fib(int n) {
  if (n ==1 || n == 2) {
    return 1;
  } else {
    int result = fib(n - 1) + fib(n - 2);
    return result;
  }

}

int main() {
  int fib_number = fib(5);
  std::cout << fib_number << std::endl;
  return 0;
}