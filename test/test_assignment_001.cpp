#include "test_util.hpp"

#include <concepts>
#include <sls/assignment.hpp>

int
main()
{
  static_assert(std::is_move_assignable_v<sls::assignment_type>);
  static_assert(std::is_move_constructible_v<sls::assignment_type>);
}
