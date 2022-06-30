#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>

#include <stl/allocator/allocator.hpp>
#include <stl/dynamic_array.hpp>
#include <stl/dynamic_vector.hpp>
#include <stl/range.hpp>

#include "cnf.hpp"

using namespace stl;

using primary_allocator_type = stack_allocator_type<0x1000, alignment_cache_line_tag>;
using secondary_allocator_type = heap_allocator_type<alignment_cache_line_tag>;
using allocator_type = fallback_allocator_type<primary_allocator_type, secondary_allocator_type>;

using array_type = dynamic_array_type<size_type, allocator_type>;

int
main(int argc, char** argv)
{
  // initialize arg1 pointer
  Assert(argc == 3, "Invalid Number of Command Line Arguments!");
  char* c = argv[1];

  /*
   * create some parsing utilities
   */

  auto curr = [&]() { return *c; };
  auto next = [&]() { return *(c++); };
  auto last = [&]() { return *(c - 1); };

  auto digit = [&]() {
    while (!std::isdigit(curr()) && curr() != '-')
      next();

    auto sig = true;
    if (curr() == '-') {
      sig = 0;
      next();
    }

    auto d = Size(0);
    while (std::isdigit(*c))
      d = (d * 10) + Size(next() - '0');
    return sig ? d : -d;
  };

  auto width = digit();
  auto height = digit();

  /*
   * assert that the solver prints the variables in right order
   */

  c = argv[2];

  std::cout << "sol:";
  for (auto _ : Range(0, width)) {
    for (auto __ : Range(0, height))
      std::cout << (digit() < 0 ? '0' : '1');
    std::cout << ';';
  }
  std::cout << std::endl;

  for (auto _ : Range(0, width)) {
    for (auto __ : Range(0, height))
      std::cout << (digit() < 0 ? ' ' : '#');
    std::cout << '\n';
  }
  std::cout << std::endl;
}
