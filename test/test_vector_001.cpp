#include "test_util.hpp"

#include <stl/dynamic_vector.hpp>
#include <stl/static_vector.hpp>
#include <stl/vector.hpp>

using type_type = stl::size_type;

template<typename vector_type>
void
test_vector()
{
  static_assert(stl::vector_concept<vector_type, type_type>);
  static_assert(std::is_move_assignable_v<vector_type>);
  static_assert(std::is_move_constructible_v<vector_type>);
  static_assert(std::ranges::range<vector_type>);
}

int
main()
{
  test_vector<stl::static_vector_type<type_type, 0x1000>>();
  test_vector<stl::dynamic_vector_type<type_type>>();
}
