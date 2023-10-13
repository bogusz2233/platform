#include <iostream>
#include <stdint.h>

extern int ApplicationMain();

int main() {
  std::cout << "Platform started" << std::endl;

  ApplicationMain();

  while (true) {
    /* code */
  }

  return 0;
}