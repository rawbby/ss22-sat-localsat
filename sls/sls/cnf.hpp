#ifndef SLS_CNF_EXTENDED_HPP
#define SLS_CNF_EXTENDED_HPP

#include "def.hpp"

#include <stl/dynamic_vector.hpp>
#include <stl/static_vector.hpp>
#include <stl/stl.hpp>

#include <iostream>
#include <type_traits>

namespace sls {

/*
 * dynamic range vector iterator declaration
 */

template<typename type_type>
struct view_iter_type
{
  type_type* data;
  const stl::size_type* range;

  MNCI view_iter_type(const view_iter_type& iter) noexcept
    : data(iter.data)
    , range(iter.range)
  {
  }

  MNCI view_iter_type(type_type* data, const stl::size_type* range) noexcept
    : data(data)
    , range(range)
  {
  }

  // satisfy the iterator concept
  MNCI stl::view_type<const type_type> operator*() const noexcept;
  MNCI stl::view_type<type_type> operator*() noexcept;
  MCI view_iter_type<type_type>& operator++() noexcept;
  MCI view_iter_type<type_type> operator++(int) noexcept; // NOLINT(cert-dcl21-cpp)
  MNCI bool operator==(const view_iter_type& other) const noexcept;
  MNCI bool operator!=(const view_iter_type& other) const noexcept;
};

template<typename type_type>
struct view_iterable_type
{
  view_iter_type<type_type> _begin;
  view_iter_type<type_type> _end;

  MI view_iterable_type(view_iter_type<type_type> begin, view_iter_type<type_type> end)
    : _begin(begin)
    , _end(end)
  {
  }

  // === iterator support ===
  MNI view_iter_type<const literal_type> begin() const noexcept { return _begin; }
  MNI view_iter_type<const literal_type> end() const noexcept { return _end; }
  MNI view_iter_type<literal_type> begin() noexcept { return _begin; }
  MNI view_iter_type<literal_type> end() noexcept { return _end; }
};

struct cnf_type
{
  stl::heap_allocator_type<stl::alignment_cache_line_tag> allocator;
  stl::dynamic_vector_type<literal_type, decltype(allocator)> cnf_buffer;
  stl::dynamic_vector_type<stl::size_type, decltype(allocator)> cnf_clauses;
  stl::dynamic_vector_type<stl::size_type, decltype(allocator)> clause_index_buffer;
  stl::dynamic_vector_type<stl::size_type, decltype(allocator)> literal_clauses;
  stl::dynamic_vector_type<stl::size_type, decltype(allocator)> literal_num_clauses;

  stl::size_type num_variables;
  stl::size_type num_literals;
  stl::size_type num_clauses;

  cnf_type(stl::size_type num_variables, stl::size_type num_clauses)
    : allocator()
    , cnf_buffer(&allocator)
    , cnf_clauses(&allocator)
    , clause_index_buffer(&allocator)
    , literal_clauses(&allocator)
    , literal_num_clauses(&allocator)
    , num_variables(num_variables)
    , num_literals(num_variables << 1)
    , num_clauses(num_clauses)
  {
    cnf_clauses.Capacity(num_clauses);
    literal_clauses.Count(num_literals);
    literal_num_clauses.Count(num_literals);
    literal_num_clauses.View().MemSet(stl::I32(0));

    // initialize the lower bound
    // of the range vectors
    cnf_clauses.Push(0);
  }

  cnf_type(cnf_type&& cnf)
    : allocator()
    , cnf_buffer(&allocator)
    , cnf_clauses(&allocator)
    , clause_index_buffer(&allocator)
    , literal_clauses(&allocator)
    , literal_num_clauses(&allocator)
    , num_variables(0)
    , num_literals(0)
    , num_clauses(0)
  {
    *this = std::move(cnf);
  }

  cnf_type& operator=(cnf_type&& other)
  {
    std::swap(allocator, other.allocator);
    std::swap(cnf_buffer, other.cnf_buffer);
    std::swap(cnf_clauses, other.cnf_clauses);
    std::swap(clause_index_buffer, other.clause_index_buffer);
    std::swap(literal_clauses, other.literal_clauses);
    std::swap(literal_num_clauses, other.literal_num_clauses);
    std::swap(num_variables, other.num_variables);
    std::swap(num_literals, other.num_literals);
    std::swap(num_clauses, other.num_clauses);
    return *this;
  }

  // === build methods ===
  MI void Push(literal_type literal) noexcept;
  MI void Push() noexcept;
  MI void PostProcess() noexcept;

  // === statistic methods ===
  MNI stl::size_type NumResolvingClauses(literal_type literal) const noexcept;
  MNI stl::view_type<const stl::size_type> ResolvingClauses(literal_type literal) const noexcept;

  // === iterable components
  MNI view_iterable_type<const literal_type> ClauseIterable() const noexcept;
  MNI view_iterable_type<literal_type> ClauseIterable() noexcept;
  MNI view_iterable_type<const stl::size_type> LiteralClausesIterable() const noexcept;
  MNI view_iterable_type<stl::size_type> LiteralClausesIterable() noexcept;
};

}

// include implementation
#include "cnf.inl"

#endif
