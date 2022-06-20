#ifndef STL_RANDOM_INL
#define STL_RANDOM_INL

#include "random.hpp"
#include <chrono>

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

template<bool deterministic>
MNI random_type
Random() noexcept
{
  if constexpr (deterministic) {
    auto ssq = std::seed_seq{ 1 };
    return { std::mt19937{ ssq } };
  }

  u64_type stack_address;
  stack_address = U64(&stack_address);

  auto dev = std::random_device{};
  auto ssq = std::seed_seq{ 1,
                            static_cast<i32_type>(stack_address),
                            static_cast<i32_type>(stack_address >> 32),
                            static_cast<i32_type>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()) };
  return { std::mt19937{ ssq } };
}

template<bool deterministic>
MNI random_type
Random(i32_type seed) noexcept
{
  if constexpr (deterministic) {
    auto ssq = std::seed_seq{ seed };
    return { std::mt19937{ ssq } };
  }

  u64_type stack_address;
  stack_address = U64(&stack_address);

  auto dev = std::random_device{};
  auto ssq = std::seed_seq{ seed,
                            static_cast<i32_type>(stack_address),
                            static_cast<i32_type>(stack_address >> 32),
                            static_cast<i32_type>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()),
                            static_cast<i32_type>(dev()) };
  return { std::mt19937{ ssq } };
}

}

#endif
