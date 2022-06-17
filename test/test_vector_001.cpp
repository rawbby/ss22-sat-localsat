#include "test_util.hpp"

#include <stl/vector.hpp>
#include <stl/dynamic_vector.hpp>
#include <stl/static_vector.hpp>

int
main()
{
  using a_static_vector_type = stl::static_vector_type<stl::size_type, 0x1000>;
  static_assert(stl::vector_concept<a_static_vector_type, stl::size_type>);

  using a_dynamic_vector_type = stl::dynamic_vector_type<stl::size_type>;
  static_assert(stl::vector_concept<a_dynamic_vector_type, stl::size_type>);
}
