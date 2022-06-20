#include "test_util.hpp"

#include <stl/dynamic_array.hpp>
#include <stl/static_array.hpp>
#include <stl/view.hpp>

using type_type = stl::size_type;

template<typename viewable_type>
void
test_vector()
{
  static_assert(stl::viewable_concept<viewable_type, type_type>);
  static_assert(std::is_move_assignable_v<viewable_type>);
  static_assert(std::is_move_constructible_v<viewable_type>);
  static_assert(std::ranges::range<viewable_type>);
}

int
main()
{
  test_vector<stl::static_array_type<type_type, 0x1000>>();
  test_vector<stl::dynamic_array_type<type_type>>();
}
