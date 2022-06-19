#ifndef SLS_CNF_INL
#define SLS_CNF_INL

#include "cnf.hpp"
#include <stl/static_vector.hpp>

namespace sls {

/*
 * satisfy the iterator concept
 */

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline stl::view_type<const type_type>
view_iter_type<type_type>::operator*() const noexcept
{
  return { &(data[range[0]]), range[1] - range[0] };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline stl::view_type<type_type>
view_iter_type<type_type>::operator*() noexcept
{
  return { &(data[range[0]]), range[1] - range[0] };
}

template<typename type_type>
[[maybe_unused]] constexpr inline view_iter_type<type_type>&
view_iter_type<type_type>::operator++() noexcept
{
  range++;
  return *this;
}

template<typename type_type>
[[maybe_unused]] constexpr inline view_iter_type<type_type> // NOLINT(cert-dcl21-cpp)
view_iter_type<type_type>::operator++(int) noexcept
{
  return { data, range++ };
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline bool
view_iter_type<type_type>::operator==(const view_iter_type& other) const noexcept
{
  stl::Assert(data == other.data, "Invalid iterator comparison!");
  return range == other.range;
}

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline bool
view_iter_type<type_type>::operator!=(const view_iter_type& other) const noexcept
{
  stl::Assert(data == other.data, "Invalid iterator comparison!");
  return range != other.range;
}

/*
 *
 */

[[maybe_unused]] inline void
cnf_type::Push(literal_type literal) noexcept
{
  cnf_buffer.Push(literal);
  ++literal_num_clauses[stl::Size(literal)];
}

[[maybe_unused]] inline void
cnf_type::Push() noexcept
{
  cnf_clauses.Push(cnf_buffer.Count());
}

[[maybe_unused]] inline void
cnf_type::PostProcess() noexcept
{
  stl::Assert(num_clauses == cnf_clauses.Count() - stl::Size(1), "Cnf was initialized with an invalid Number of Clauses!");
  num_clauses = cnf_clauses.Count();

  // for each sub vector create an index counter
  auto i = stl::dynamic_array_type<stl::size_type, decltype(allocator)>(&allocator, num_literals);
  i.View().MemSet(stl::I32(0));

  // initialize lookup data structures
  clause_index_buffer.Count(cnf_buffer.Count());
  literal_clauses.Count(num_literals + 1);

  // initialize literal clauses
  auto total_size = stl::Size(0);
  for (auto j = stl::Size(0); j < num_literals; ++j) {
    total_size += literal_num_clauses[j];
    literal_clauses[j + 1] = total_size;
  }

  auto clause_index = stl::Size(0);
  const auto clauses = cnf_clauses.Count() - 1;

  for (auto c = stl::Size(0); c < clauses; ++c) {
    auto clause_begin = cnf_clauses[c];
    auto clause_end = cnf_clauses[c+1];

    for (auto l = clause_begin; l < clause_end; ++l) {
      auto literal = cnf_buffer[l];

      auto index = i[literal]++;
      literal_clauses[literal + index] = clause_index;
    }
  }

  for (auto clause : ClauseIterable()) {
    const auto clause_end = clause.end();

    const auto last = clause_end - 1;

    for (auto clause_i = clause.begin(); clause_i != clause_end; clause_i++) {

      auto literal = *clause_i;
      auto index = i[literal]++;
      literal_clauses[literal + index] = clause_index;
    }

    clause_index += stl::Size(1);
  }
}

[[maybe_unused]] [[nodiscard]] inline stl::size_type
cnf_type::NumResolvingClauses(literal_type literal) const noexcept
{
  return literal_num_clauses[literal];
}

[[maybe_unused]] [[nodiscard]] inline stl::view_type<const stl::size_type>
cnf_type::ResolvingClauses(literal_type literal) const noexcept
{
  auto lower = literal_clauses[literal];
  auto upper = literal_clauses[literal + 1];
  return clause_index_buffer.View().Range(lower, upper);
}

MNI view_iterable_type<const literal_type>
cnf_type::ClauseIterable() const noexcept
{
  return { { cnf_buffer.begin(), cnf_clauses.begin() }, { cnf_buffer.begin(), cnf_clauses.end()-1 } };
}

MNI view_iterable_type<literal_type>
cnf_type::ClauseIterable() noexcept
{
  return { { cnf_buffer.begin(), cnf_clauses.begin() }, { cnf_buffer.begin(), cnf_clauses.end()-1 } };
}

MNI view_iterable_type<const stl::size_type>
cnf_type::LiteralClausesIterable() const noexcept
{
  return { { clause_index_buffer.begin(), literal_clauses.begin() }, { clause_index_buffer.begin(), literal_clauses.end()-1 } };
}

MNI view_iterable_type<stl::size_type>
cnf_type::LiteralClausesIterable() noexcept
{
  return { { clause_index_buffer.begin(), literal_clauses.begin() }, { clause_index_buffer.begin(), literal_clauses.end()-1 } };
}

}

#endif
