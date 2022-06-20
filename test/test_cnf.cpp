#include "test_util.hpp"

#include <concepts>
#include <sls/cnf.hpp>

int
main()
{
  static_assert(std::is_move_assignable_v<sls::cnf_type>);
  static_assert(std::is_move_constructible_v<sls::cnf_type>);
}
