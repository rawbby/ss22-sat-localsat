#ifndef SLS_DEF_HPP
#define SLS_DEF_HPP

#include <stl/random.hpp>
#include <stl/stl.hpp>

namespace sls {
using namespace stl;

STL_DEFINE_INTEGRAL_CONSTRUCTOR(i16_type, literal_type, Literal)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(i16_type, variable_type, Variable)

// just define what is expected by this solver

[[maybe_unused]] constexpr auto MAX_VARIABLES = Size(384);              ///< 64 bytes = 32 literals => 12 cache lines
[[maybe_unused]] constexpr auto MAX_LITERALS = MAX_VARIABLES * Size(2); ///< 64 bytes = 32 literals => 12 cache lines
[[maybe_unused]] constexpr auto MAX_CLAUSES = Size(1'920);              ///< approx 5 x MAX_VARIABLES
[[maybe_unused]] constexpr auto MAX_CNF_LITERALS = Size(9'600); ///< approx 5 literals per clause; 64 bytes = 32 literals => 300 cache lines

[[maybe_unused]] [[nodiscard]] constexpr inline literal_type
Literal(variable_type var, i8_type sign) noexcept
{
  Assert(var < MAX_VARIABLES, "Invalid Variable passed!");
  auto literal = (var << 1) | sign;
  return literal;
}

}

#endif
