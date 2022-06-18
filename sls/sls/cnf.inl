#ifndef SLS_CNF_INL
#define SLS_CNF_INL

#include "cnf.hpp"
#include <stl/static_vector.hpp>

namespace sls {

[[maybe_unused]] inline void
cnf_type::Push(literal_type literal) noexcept
{
  cnf.Push(literal);
  *(num_clauses_for_literals.At(stl::Size(literal))) += stl::Size(1);
}

[[maybe_unused]] inline void
cnf_type::Push() noexcept
{
  cnf.Push();
}

[[maybe_unused]] inline void
cnf_type::PostProcess() noexcept
{
  stl::Assert(!num_clauses || num_clauses == cnf.Count(), "Cnf was initialized with an invalid Number of Clauses!");
  num_clauses = cnf.Count();

  // for each sub vector create an index counter
  auto i = stl::StaticVector<stl::size_type, SLS_MAX_LITERALS>();
  i.Count(num_literals);
  i.View().MemSet(stl::I32(0));

  auto& n = num_clauses_for_literals;
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

[[maybe_unused]] [[nodiscard]] inline stl::size_type
cnf_type::NumResolvingClauses(literal_type literal) const noexcept
{
  return *(num_clauses_for_literals.At(literal));
}

[[maybe_unused]] [[nodiscard]] inline stl::view_type<const stl::size_type>
cnf_type::ResolvingClauses(literal_type literal) const noexcept
{
  return vc.At(literal);
}

[[maybe_unused]] [[nodiscard]] inline vector_stack_iter_type<literal_type>
cnf_type::begin() noexcept
{
  return cnf.begin();
}

[[maybe_unused]] [[nodiscard]] inline vector_stack_iter_type<literal_type>
cnf_type::end() noexcept
{
  return cnf.end();
}

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] inline void
Cnf(cnf_type* cnf, stl::size_type num_variables, stl::size_type num_clauses) noexcept
{
  cnf->num_variables = num_variables;
  cnf->num_literals = num_variables << 1;
  cnf->num_clauses = num_clauses;

  //stl::VectorStack(&cnf->cnf);
  //stl::VectorStack(&cnf->vc);

  cnf->cnf.Capacity(num_clauses);
  cnf->num_clauses_for_literals.Count(cnf->num_literals);
  cnf->num_clauses_for_literals.View().MemSet(stl::I32(0));
}

[[maybe_unused]] inline void
Cnf(cnf_type* cnf, stl::size_type num_variables) noexcept
{
  Cnf(cnf, num_variables, stl::Size(0));
}

[[maybe_unused]] [[nodiscard]] inline cnf_type
Cnf(stl::size_type num_variables, stl::size_type num_clauses) noexcept
{
  cnf_type cnf{};
  Cnf(&cnf, num_variables, num_clauses);
  return cnf;
}

[[maybe_unused]] [[nodiscard]] inline cnf_type
Cnf(stl::size_type num_variables) noexcept
{
  cnf_type cnf{};
  Cnf(&cnf, num_variables, stl::Size(0));
  return cnf;
}

}

#endif
