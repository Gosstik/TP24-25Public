#include "fibo.h"

int fibo(int val) {
  if (val == 1 || val == 2) {
    return 1;
  }
  return fibo(val - 1) + fibo(val - 2);
}
