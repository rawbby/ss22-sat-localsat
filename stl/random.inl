#ifndef STL_RANDOM_INL
#define STL_RANDOM_INL

#include "random.hpp"

namespace stl {

//  __  __   _____   _____   _   _    ___    ____    ____
// |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
// | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
// | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
// |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

[[maybe_unused]] [[nodiscard]] inline bool
random_type::randBool() noexcept
{
  auto distribution = std::uniform_int_distribution<std::mt19937::result_type>(0, 1);
  return distribution(engine);
}

[[maybe_unused]] [[nodiscard]] inline i32_type
random_type::randInt(i32_type upper) noexcept
{
  Assert(0 <= upper - 1, "Can not create Distribution with 0 > Upper-1!");
  auto distribution = std::uniform_int_distribution<std::mt19937::result_type>(0, upper - 1);
  return distribution(engine);
}

[[maybe_unused]] [[nodiscard]] inline i32_type
random_type::randInt(i32_type lower, i32_type upper) noexcept
{
  Assert(lower <= upper - 1, "Can not create Distribution with Lower > Upper-1!");
  auto distribution = std::uniform_int_distribution<std::mt19937::result_type>(lower, upper - 1);
  return distribution(engine);
}

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] [[nodiscard]] inline random_type
Random() noexcept
{
  random_type random;
  random.engine = std::mt19937(std::random_device{}());
  return random;
}
[[maybe_unused]] [[nodiscard]] inline random_type
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
