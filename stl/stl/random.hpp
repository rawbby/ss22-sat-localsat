#ifndef STL_RANDOM_HPP
#define STL_RANDOM_HPP

#include "stl.hpp"

#include <random>

namespace stl {

struct random_type
{
  std::mt19937 engine;

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  MNI bool_type RandBool() noexcept;

  MNI i32_type RandInt(i32_type upper) noexcept;

  MNI i32_type RandInt(i32_type lower, i32_type upper) noexcept;
};

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

template<bool deterministic = false>
MNI random_type
Random() noexcept;

template<bool deterministic = false>
MNI random_type
Random(i32_type seed) noexcept;

}

// include implementation
#include "random.inl"

#endif
