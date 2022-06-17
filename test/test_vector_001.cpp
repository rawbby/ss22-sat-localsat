#include "test_util.hpp"

#include <stl/dynamic_vector.hpp>
#include <stl/static_vector.hpp>
#include <stl/vector.hpp>
#include <stl/view.hpp>

int
main()
{
  static_assert(stl::vector_concept<stl::static_vector_type<stl::size_type, 0x1000>, stl::size_type>);
  static_assert(stl::vector_concept<stl::dynamic_vector_type<stl::size_type>, stl::size_type>);

  static_assert(stl::view_convertible_concept<stl::static_vector_type<stl::size_type, 0x1000>, stl::size_type>);
  static_assert(stl::view_convertible_concept<stl::dynamic_vector_type<stl::size_type>, stl::size_type>);
}
