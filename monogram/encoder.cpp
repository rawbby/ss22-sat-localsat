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

using vector_type = dynamic_vector_type<size_type, allocator_type>;
using array_type = dynamic_array_type<size_type, allocator_type>;
using consumer_type = std::function<void(view_type<size_type>)>;
using index_translator_type = std::function<size_type(size_type, size_type)>;
using monogram_type = cnf_type;

void
SetOccupancy(view_type<size_type> line, view_type<size_type> free_spaces, view_type<size_type> occupancy)
{
  auto i = Size(0);

  for ([[maybe_unused]] auto _ : Range(0, free_spaces[0]))
    occupancy[i++] = 0;
  for ([[maybe_unused]] auto _ : Range(0, line[0]))
    occupancy[i++] = 1;

  for (auto index : Range(1, line.Count())) {
    for ([[maybe_unused]] auto _ : Range(0, free_spaces[index] + 1))
      occupancy[i++] = 0;
    for ([[maybe_unused]] auto _ : Range(0, line[index]))
      occupancy[i++] = 1;
  }

  for ([[maybe_unused]] auto _ : Range(0, free_spaces[free_spaces.Count() - 1]))
    occupancy[i++] = 0;
}

void
GenerateALO(monogram_type* monogram, view_type<size_type> variables)
{
  for (auto literal : variables)
    monogram->Push(literal);
  monogram->Push();
}

void
GenerateAMO(monogram_type* monogram, view_type<size_type> x)
{
  // Sequential Counter Encoding

  auto n = x.Count();
  if (n < 2)
    return;

  // generate n-1 variables:
  auto s = monogram->GenerateVariables(n - 1);

  // -x[0] or s[0]
  monogram->Push(-x[0]);
  monogram->Push(s[0]);
  monogram->Push();

  // -x[n-1] or -s[n-2]
  monogram->Push(-x[n - 1]);
  monogram->Push(-s[n - 2]);
  monogram->Push();

  // for (0 < i < n-1)
  for (auto i : stl::Range(1, n - 1)) {

    //  -x[i] or s[i]
    monogram->Push(-x[i]);
    monogram->Push(s[i]);
    monogram->Push();

    //  -s[i-1] or s[i]
    monogram->Push(-s[i - 1]);
    monogram->Push(s[i]);
    monogram->Push();

    //  -x[i] or -s[i-1]
    monogram->Push(-x[i]);
    monogram->Push(-s[i - 1]);
    monogram->Push();
  }
}

void
GenerateFreeSpacesCombinations(monogram_type* monogram,
                               view_type<size_type> free_spaces,
                               size_type free_space,
                               consumer_type consumer,
                               size_type depth = 0)
{
  if (depth == free_spaces.Count() - 1) {
    free_spaces[depth] = free_space;
    consumer(free_spaces);
    return;
  }

  for (auto this_free_space : Range(0, free_space + 1)) {
    free_spaces[depth] = this_free_space;
    GenerateFreeSpacesCombinations(monogram, free_spaces, free_space - this_free_space, consumer, depth + 1);
  }
}

void
GenerateLineConstraint(monogram_type* monogram,
                       view_type<size_type> row_digits,
                       size_type line,
                       size_type length,
                       allocator_type* allocator,
                       index_translator_type index_translator)
{
  auto occupied = std::accumulate(row_digits.begin(), row_digits.end(), Size(0));
  auto free_space = length - occupied - row_digits.Count() + 1;
  Assert(free_space >= 0, "To many occupied Tiles!");

  auto occupancy = array_type(allocator, length);
  auto temporaries = vector_type(allocator);

  auto consumer = [&](view_type<size_type> free_spaces) {
    SetOccupancy(row_digits, free_spaces, occupancy.View());

    /*
     * constraint 1:
     *
     * temporary variable s -> exact combination c
     * =  s -> c
     * = -s or c
     */

    auto s = monogram->GenerateVariables(1)[0];
    for (auto i : Range(0, length)) {
      auto v = index_translator(line, i);
      monogram->Push(-s);
      monogram->Push(occupancy[i] ? v : -v);
      monogram->Push();
    }

    // prepare constraint 2 which is handled
    // after all combinations are consumed
    temporaries.Push(s);
  };

  // free spaces can occur before each segment and at the very end
  auto free_spaces = array_type(allocator, row_digits.Count() + 1);
  GenerateFreeSpacesCombinations(monogram, free_spaces.View(), free_space, consumer);

  // constraint 2:
  // exactly_once({v | all temporary variables of a row})
  GenerateALO(monogram, temporaries.View());
  GenerateAMO(monogram, temporaries.View());
}

void
GenerateRowConstraint(monogram_type* monogram, view_type<size_type> row_digits, size_type row, size_type width, allocator_type* allocator)
{
  auto index_translator = [width](size_type row, size_type column) { return 1 + (row * width) + column; };
  GenerateLineConstraint(monogram, row_digits, row, width, allocator, index_translator);
}

void
GenerateColumnConstraint(monogram_type* monogram,
                         view_type<size_type> row_digits,
                         size_type column,
                         size_type width,
                         size_type height,
                         allocator_type* allocator)
{
  auto index_translator = [width](size_type column, size_type row) { return 1 + (row * width) + column; };
  GenerateLineConstraint(monogram, row_digits, column, height, allocator, index_translator);
}

int
main(int argc, char** argv)
{
  // initialize arg1 pointer
  Assert(argc == 2, "Invalid Number of Command Line Arguments!");
  char* c = argv[1];

  /*
   * create some parsing utilities
   */

  auto next = [&]() { return *(c++); };
  auto last = [&]() { return *(c - 1); };

  auto digit = [&]() {
    auto d = Size(0);
    while (std::isdigit(*c))
      d = (d * 10) + Size(next() - '0');
    return d;
  };

  // parse width
  auto width = digit();
  Assert(next() == ',', "Unexpected Symbol parsed!");

  // parse height
  auto height = digit();
  Assert(next() == ':', "Unexpected Symbol parsed!");

  /*
   * initialize memory management
   * for utility container and create
   * monogram container.
   */

  auto allocator = allocator_type();
  auto monogram = monogram_type(width * height);

  /*
   * parse line digits
   */

  auto line_digits = vector_type(&allocator);

  // unfortunately we need to write two very similar
  // parsing loops for rows and columns. maybe someone
  // can find a more sexy way that generalizes this two
  // loops.

  for (auto row : Range(0, height)) {

    line_digits.Count(0);

    do {
      line_digits.Push(digit());
    } while (next() == ',');
    Assert(last() == ';', "Unexpected Symbol parsed!");

    GenerateRowConstraint(&monogram, line_digits.View(), row, width, &allocator);
  }

  for (auto column : Range(0, width)) {

    line_digits.Count(0);

    do {
      line_digits.Push(digit());
    } while (next() == ',');
    Assert(last() == ';', "Unexpected Symbol parsed!");

    GenerateColumnConstraint(&monogram, line_digits.View(), column, width, height, &allocator);
  }

  monogram.Print();
}
