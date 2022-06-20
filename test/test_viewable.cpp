#include "test_util.hpp"

#include <stl/dynamic_array.hpp>
#include <stl/dynamic_vector.hpp>
#include <stl/static_array.hpp>
#include <stl/static_vector.hpp>
#include <stl/view.hpp>

using type_type = stl::size_type;

template<typename vector_type>
void
test_viewable()
{
  static_assert(stl::view_convertible_concept<vector_type, type_type>);
  static_assert(stl::viewable_concept<vector_type, type_type>);
}

int
main()
{
  using a_view_type = stl::view_type<type_type>;
  static_assert(stl::viewable_concept<a_view_type, type_type>);

  test_viewable<stl::static_array_type<type_type, 0x1000>>();
  test_viewable<stl::static_vector_type<type_type, 0x1000>>();
  test_viewable<stl::dynamic_array_type<type_type>>();
  test_viewable<stl::dynamic_vector_type<type_type>>();
}
