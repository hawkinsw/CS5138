#include <cmath>
#include <stdint.h>
#include <stdio.h>

double end_speed(double starting_speed, double coefficient_of_friction,
                 double distance, uint64_t mass) {

  auto gravity = 9.8;
  auto decel = coefficient_of_friction * gravity;
  auto squared_result =
      (starting_speed * starting_speed) - 2 * decel * distance;
  return std::sqrt(squared_result);
}

int main() {
  printf("%f\n", end_speed(50.0, .75, 12, 0xdeadb));
  return 0;
}
