#ifndef STL_RANDOM_INL
#define STL_RANDOM_INL

#include "random.hpp"

namespace stl {

MNI bool
random_type::RandBool() noexcept
{
  auto distribution = std::uniform_int_distribution<std::mt19937::result_type>(0, 1);
  return distribution(engine);
}

MNI i32_type
random_type::RandInt(i32_type upper) noexcept
{
  Assert(0 <= upper - 1, "Can not create Distribution with 0 > Upper-1!");
  auto distribution = std::uniform_int_distribution<std::mt19937::result_type>(0, upper - 1);
  return distribution(engine);
}

MNI i32_type
random_type::RandInt(i32_type lower, i32_type upper) noexcept
{
  Assert(lower <= upper - 1, "Can not create Distribution with Lower > Upper-1!");
  auto distribution = std::uniform_int_distribution<std::mt19937::result_type>(lower, upper - 1);
  return distribution(engine);
}

MNI random_type
Random(i32_type seed) noexcept
{
  random_type random;
  random.engine = std::mt19937(std::random_device{}());

  auto ssq = std::seed_seq{ seed };
  random.engine.seed(ssq);
  return random;
}

}

#endif
