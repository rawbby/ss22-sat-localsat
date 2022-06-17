#include "test_util.hpp"

#include <stl/dynamic_vector.hpp>
#include <stl/static_vector.hpp>
#include <stl/array.hpp>
#include <stl/view.hpp>

int
main()
{
  using a_view_type = stl::view_type<stl::size_type>;
  static_assert(stl::viewable_concept<a_view_type, stl::size_type>);

  using a_static_array_type = stl::array_type<stl::size_type, 0x1000>;
  static_assert(stl::view_convertible_concept<a_static_array_type, stl::size_type>);
  static_assert(stl::viewable_concept<a_static_array_type, stl::size_type>);

  using a_dynamic_array_type = stl::array_type<stl::size_type, 0x1000>;
  static_assert(stl::view_convertible_concept<a_dynamic_array_type, stl::size_type>);
  static_assert(stl::viewable_concept<a_dynamic_array_type, stl::size_type>);

  using a_static_vector_type = stl::static_vector_type<stl::size_type, 0x1000>;
  static_assert(stl::view_convertible_concept<a_static_vector_type, stl::size_type>);
  static_assert(stl::viewable_concept<a_static_vector_type, stl::size_type>);

  using a_dynamic_vector_type = stl::dynamic_vector_type<stl::size_type>;
  static_assert(stl::view_convertible_concept<a_dynamic_vector_type, stl::size_type>);
  static_assert(stl::viewable_concept<a_dynamic_vector_type, stl::size_type>);
}
