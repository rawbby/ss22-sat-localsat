#ifndef SLS_ASSIGNMENT_HPP
#define SLS_ASSIGNMENT_HPP

#include <stl/random.hpp>
#include <stl/vector.hpp>
#include <stl/view.hpp>

#include "cnf.hpp"
#include "sls.hpp"

namespace sls {
using namespace stl;

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

struct assignment_type
{
  vector_type<i8_type, MAX_VARIABLES> assign;
  vector_type<size_type, MAX_CLAUSES> satisfied_counts;

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  [[maybe_unused]] constexpr inline void Flip(const cnf_type* cnf, variable_type variable) noexcept;

  [[maybe_unused]] inline void RandomFlip(const cnf_type* cnf, random_type random) noexcept;

  [[maybe_unused]] constexpr inline void BestFlip(const cnf_type* cnf) noexcept;

  [[maybe_unused]] constexpr inline void RandomReset(const cnf_type* cnf, random_type* random) noexcept;

  [[maybe_unused]] constexpr inline void UpdateStats(const cnf_type* cnf) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline float Score() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline size_type FlipStat(const cnf_type* cnf, variable_type variable) noexcept;
};

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] [[nodiscard]] constexpr inline assignment_type
Assignment(const cnf_type* cnf) noexcept;

[[maybe_unused]] [[nodiscard]] inline assignment_type
Assignment(const cnf_type* cnf, random_type* random) noexcept;

//  ___   _____   _____   ____       _      _____    ___    ____
// |_ _| |_   _| | ____| |  _ \     / \    |_   _|  / _ \  |  _ \
//  | |    | |   |  _|   | |_) |   / _ \     | |   | | | | | |_) |
//  | |    | |   | |___  |  _ <   / ___ \    | |   | |_| | |  _ <
// |___|   |_|   |_____| |_| \_\ /_/   \_\   |_|    \___/  |_| \_\

[[maybe_unused]] [[nodiscard]] constexpr inline view_iterator_type<i8_type>
Iterator(assignment_type* assign) noexcept;

}

// include implementation
#include "assignment.inl"

#endif
