#ifndef SLS_ASSIGNMENT_HPP
#define SLS_ASSIGNMENT_HPP

#include <stl/random.hpp>
#include <stl/static_vector.hpp>
#include <stl/view.hpp>

#include "cnf.hpp"
#include "def.hpp"

namespace sls {

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

struct assignment_type
{
  stl::static_vector_type<stl::i8_type, SLS_MAX_VARIABLES> assign;
  stl::static_vector_type<stl::size_type, SLS_MAX_CLAUSES> satisfied_counts;
  stl::size_type loop_offset;

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  [[maybe_unused]] constexpr inline void Flip(const cnf_type* cnf, variable_type variable) noexcept;

  [[maybe_unused]] inline void RandomFlip(const cnf_type* cnf, stl::random_type random) noexcept;

  [[maybe_unused]] constexpr inline void BestFlip(const cnf_type* cnf) noexcept;

  [[maybe_unused]] inline void BestFlip(const cnf_type* cnf, stl::random_type* random) noexcept;

  [[maybe_unused]] constexpr inline void RandomReset(const cnf_type* cnf, stl::random_type* random) noexcept;

  [[maybe_unused]] constexpr inline void UpdateStats(const cnf_type* cnf) noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline float Score() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline stl::size_type FlipStat(const cnf_type* cnf, variable_type variable) noexcept;

  // === iterator support ===

  [[maybe_unused]] [[nodiscard]] constexpr inline stl::i8_type* begin() noexcept;

  [[maybe_unused]] [[nodiscard]] constexpr inline stl::i8_type* end() noexcept;
};

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] constexpr inline void
Assignment(assignment_type* assign, const cnf_type* cnf) noexcept;

[[maybe_unused]] [[nodiscard]] constexpr inline assignment_type
Assignment(const cnf_type* cnf) noexcept;

[[maybe_unused]] inline void
Assignment(assignment_type* assign, const cnf_type* cnf, stl::random_type* random) noexcept;

[[maybe_unused]] [[nodiscard]] inline assignment_type
Assignment(const cnf_type* cnf, stl::random_type* random) noexcept;

}

// include implementation
#include "assignment.inl"

#endif
