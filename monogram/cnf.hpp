#ifndef MONOGRAM_CNF_HPP
#define MONOGRAM_CNF_HPP

#include <stl/allocator/allocator.hpp>
#include <stl/dynamic_array.hpp>
#include <stl/dynamic_vector.hpp>
#include <stl/range.hpp>

auto cnf_allocator_type = stl::heap_allocator_type<stl::alignment_page_tag>();

struct cnf_type
{
  stl::dynamic_vector_type<char, decltype(cnf_allocator_type)> buffer;
  stl::size_type num_variables;
  stl::size_type num_clauses;

  MI cnf_type(stl::size_type num_reserved_variables) noexcept
    : buffer(&cnf_allocator_type)
    , num_variables(num_reserved_variables)
    , num_clauses()
  {
    // preallocate one page
    buffer.Capacity(stl::alignment_page_tag::alignment / sizeof(char));
  }

  M void _Push(stl::size_type literal) noexcept
  {
    // recursive approach to create
    // a literal string. this is needed
    // due to the limitations of the
    // char vector. maybe a string buffer
    // will be supported later.

    if (!literal)
      return;

    auto digit = static_cast<char>('0' + (literal % 10));
    _Push(literal / 10);
    buffer.Push(digit);
  }

  MI void Push(stl::size_type literal) noexcept
  {
    // add the literal to the cnf

    // handle negation here as
    // it is not supported by
    // the recursive _Push.
    if (literal < 0) {
      buffer.Push('-');
      literal = -literal;
    }

    _Push(literal);
    buffer.Push(' ');
  }

  MI void Push() noexcept
  {
    buffer.Push('0');
    buffer.Push('\n');
    ++num_clauses;
  }

  MNCI stl::range_type<stl::size_type> GenerateVariables(stl::size_type count) noexcept
  {
    num_variables += count;
    return { num_variables - count + 1, num_variables + 1 };
  }

  MI void Print() noexcept
  {
    // add a marker that makes
    // the buffer a c string.
    buffer.Push('\0');

    // print the header and
    // print the cnf formula.
    std::cout << "p cnf " << num_variables << ' ' << num_clauses << '\n';
    std::cout << buffer.begin() << std::flush;

    // remove the marker
    // in case the cnf will
    // be used again.
    buffer.Pop();
  }
};

#endif
