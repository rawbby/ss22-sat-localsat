#ifndef SLS_CNF_INL
#define SLS_CNF_INL

#include "cnf.hpp"

namespace sls {
using namespace stl;

[[maybe_unused]] constexpr inline void
cnf_type::Push(literal_type literal) noexcept
{
  cnf.Push(literal);
  *(num_clauses_for_literals.At(Size(literal))) += Size(1);
}

[[maybe_unused]] constexpr inline void
cnf_type::Push() noexcept
{
  cnf.Push();
}

[[maybe_unused]] constexpr inline void
cnf_type::PostProcess() noexcept
{
  // for each sub vector create an index counter
  auto i = Vector<size_type, MAX_LITERALS>();
  i.Count(num_literals);
  View(&i).MemSet(I32(0));

  auto n = num_clauses_for_literals;
  auto m = num_literals;

  {
    // hack into cnf.vc
    vc.buffer.Count(cnf.buffer.Count());
    vc.ranges.Count(num_literals + Size(1));
    auto total_size = Size(0);
    for (auto j = Size(0); j < m; ++j) {
      total_size += *n.At(j);
      *(vc.ranges.At(j + Size(1))) = total_size;
    }
  }

  {
    auto clause_index = Size(0);

    for (auto clause : cnf) {
      for (auto literal : clause) {

        auto view = vc.At(literal);
        auto index = (*i.At(literal))++;

        *(view.At(index)) = clause_index;
      }

      clause_index += Size(1);
    }
  }
}

[[maybe_unused]] [[nodiscard]] constexpr inline size_type
cnf_type::NumResolvingClauses(literal_type literal) const noexcept
{
  return *(num_clauses_for_literals.At(literal));
}

[[maybe_unused]] [[nodiscard]] constexpr inline view_type<const size_type>
cnf_type::ResolvingClauses(literal_type literal) const noexcept
{
  return vc.At(literal);
}

[[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type<literal_type>
cnf_type::begin() noexcept
{
  return cnf.begin();
}

[[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type<literal_type>
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
CnfExtended(size_type num_variables, size_type num_clauses) noexcept
{
  cnf_type cnf;

  cnf.num_variables = num_variables;
  cnf.num_literals = num_variables << 1;
  cnf.num_clauses = num_clauses;

  cnf.cnf = VectorStack<literal_type, MAX_CLAUSES, MAX_CNF_LITERALS>();
  cnf.vc = VectorStack<size_type, MAX_LITERALS, MAX_CNF_LITERALS>();

  cnf.num_clauses_for_literals = Vector<size_type, MAX_LITERALS>();
  cnf.num_clauses_for_literals.Count(cnf.num_literals);

  // if constexpr context the whole
  // vec is already zero initialized
  if (!std::is_constant_evaluated())
    View(&cnf.num_clauses_for_literals, Size(0), cnf.num_literals).MemSet(I32(0));

  return cnf;
}

}

#endif
