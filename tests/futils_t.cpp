#include <criterion/criterion.h>
#include "futils.hpp"

Test(IntegerRange, Generation) {
  futils::IntegralRange<int> range(0, 100);
  for (auto i = 0; i < 10; i++) {
    auto number = range.getRandom();
    cr_assert(number >= 0 && number <= 100, "Generated number is out of range");
  } 
}
