#ifndef SLS_CNF_INL
#define SLS_CNF_INL

#include "cnf.hpp"

namespace sls {

[[maybe_unused]] constexpr inline void
cnf_type::Push(literal_type literal) noexcept
{
  cnf.Push(literal);
  *(num_clauses_for_literals.At(stl::Size(literal))) += stl::Size(1);
}

[[maybe_unused]] constexpr inline void
cnf_type::Push() noexcept
{
  cnf.Push();
}

[[maybe_unused]] constexpr inline void
cnf_type::PostProcess() noexcept
{
  stl::Assert(!num_clauses || num_clauses == cnf.Count(), "Cnf was initialized with an invalid Number of Clauses!");
  num_clauses = cnf.Count();

  // for each sub vector create an index counter
  auto i = stl::StaticVector<stl::size_type, SLS_MAX_LITERALS>();
  i.Count(num_literals);
  i.ToView().MemSet(stl::I32(0));

  auto n = num_clauses_for_literals;
  auto m = num_literals;

  {
    // hack into cnf.vc
    vc.buffer.Count(cnf.buffer.Count());
    vc.ranges.Count(num_literals + stl::Size(1));
    auto total_size = stl::Size(0);
    for (auto j = stl::Size(0); j < m; ++j) {
      total_size += *n.At(j);
      *(vc.ranges.At(j + stl::Size(1))) = total_size;
    }
  }

  {
    auto clause_index = stl::Size(0);

    for (auto clause : cnf) {
      for (auto literal : clause) {

        auto view = vc.At(literal);
        auto index = (*i.At(literal))++;

        *(view.At(index)) = clause_index;
      }

      clause_index += stl::Size(1);
    }
  }
}

[[maybe_unused]] [[nodiscard]] constexpr inline stl::size_type
cnf_type::NumResolvingClauses(literal_type literal) const noexcept
{
  return *(num_clauses_for_literals.At(literal));
}

[[maybe_unused]] [[nodiscard]] constexpr inline stl::view_type<const stl::size_type>
cnf_type::ResolvingClauses(literal_type literal) const noexcept
{
  return vc.At(literal);
}

[[maybe_unused]] [[nodiscard]] constexpr inline stl::vector_stack_iter_type<literal_type>
cnf_type::begin() noexcept
{
  return cnf.begin();
}

[[maybe_unused]] [[nodiscard]] constexpr inline stl::vector_stack_iter_type<literal_type>
cnf_type::end() noexcept
{
  return cnf.end();
}

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] [[nodiscard]] constexpr inline cnf_type
CnfExtended(stl::size_type num_variables, stl::size_type num_clauses) noexcept
{
  cnf_type cnf;
  cnf.num_variables = num_variables;
  cnf.num_literals = num_variables << 1;
  cnf.num_clauses = num_clauses;

  VectorStack<literal_type, SLS_MAX_CLAUSES, SLS_MAX_CNF_LITERALS>(&cnf.cnf);
  VectorStack<stl::size_type, SLS_MAX_LITERALS, SLS_MAX_CNF_LITERALS>(&cnf.vc);

  StaticVector<stl::size_type, SLS_MAX_LITERALS>(&cnf.num_clauses_for_literals);
  cnf.num_clauses_for_literals.Count(cnf.num_literals);
  cnf.num_clauses_for_literals.ToView().MemSet(stl::I32(0));

  return cnf;
}

[[maybe_unused]] [[nodiscard]] constexpr inline cnf_type
CnfExtended(stl::size_type num_variables) noexcept
{
  return CnfExtended(num_variables, stl::Size(0));
}

}

#endif
