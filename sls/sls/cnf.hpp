#ifndef SLS_CNF_EXTENDED_HPP
#define SLS_CNF_EXTENDED_HPP

#include "def.hpp"
#include "vector_stack.hpp"

#include <stl/dynamic_vector.hpp>
#include <stl/static_vector.hpp>
#include <stl/stl.hpp>

#include <iostream>
#include <type_traits>

namespace sls {

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

struct cnf_type
{
  using cnf_stack_type = vector_stack_type<literal_type, stl::dynamic_vector_type<literal_type>, stl::dynamic_vector_type<stl::size_type>>;
  using literal_clause_lookup_type = vector_stack_type<stl::size_type, stl::dynamic_vector_type<stl::size_type>, stl::dynamic_vector_type<stl::size_type>>;
  using clause_count_type = stl::dynamic_vector_type<stl::size_type>;

  // base cnf formula
  cnf_stack_type cnf;

  // statistical lookup
  literal_clause_lookup_type vc;
  clause_count_type num_clauses_for_literals;

  stl::size_type num_variables;
  stl::size_type num_literals;
  stl::size_type num_clauses;

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  // === build methods ===

  [[maybe_unused]] inline void Push(literal_type literal) noexcept;

  [[maybe_unused]] inline void Push() noexcept;

  [[maybe_unused]] inline void PostProcess() noexcept;

  // === statistic methods ===

  [[maybe_unused]] [[nodiscard]] inline stl::size_type NumResolvingClauses(literal_type literal) const noexcept;

  [[maybe_unused]] [[nodiscard]] inline stl::view_type<const stl::size_type> ResolvingClauses(literal_type literal) const noexcept;

  // ==- iterator support ===

  [[maybe_unused]] [[nodiscard]] inline vector_stack_iter_type<literal_type> begin() noexcept;

  [[maybe_unused]] [[nodiscard]] inline vector_stack_iter_type<literal_type> end() noexcept;
};

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] inline void
Cnf(cnf_type* cnf, stl::size_type num_variables, stl::size_type num_clauses) noexcept;

[[maybe_unused]] inline void
Cnf(cnf_type* cnf, stl::size_type num_variables) noexcept;

[[maybe_unused]] [[nodiscard]] inline cnf_type
Cnf(stl::size_type num_variables, stl::size_type num_clauses) noexcept;

[[maybe_unused]] [[nodiscard]] inline cnf_type
Cnf(stl::size_type num_variables) noexcept;

}

// include implementation
#include "cnf.inl"

#endif
