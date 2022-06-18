#ifndef SLS_DEF_HPP
#define SLS_DEF_HPP

#include <stl/random.hpp>
#include <stl/stl.hpp>

namespace sls {

STL_DEFINE_INTEGRAL_CONSTRUCTOR(stl::i16_type, literal_type, Lit)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(stl::i16_type, variable_type, Var)

// just define what is expected by this solver

#ifndef SLS_OPTION_MAX_VARIABLES
/// 64 bytes = 32 literals => 12 cache lines
[[maybe_unused]] constexpr auto SLS_MAX_VARIABLES = stl::Size(384);
#else
[[maybe_unused]] constexpr auto SLS_MAX_VARIABLES = stl::Size(SLS_OPTION_MAX_VARIABLES);
#endif

[[maybe_unused]] constexpr auto SLS_MAX_LITERALS = SLS_MAX_VARIABLES * stl::Size(2);

#ifndef SLS_OPTION_MAX_CLAUSES
/// approx 5 x SLS_MAX_VARIABLES
[[maybe_unused]] constexpr auto SLS_MAX_CLAUSES = SLS_MAX_VARIABLES * stl::Size(5);
#else
[[maybe_unused]] constexpr auto SLS_MAX_CLAUSES = stl::Size(SLS_OPTION_MAX_CLAUSES);
#endif

#ifndef SLS_OPTION_MAX_CNF_LITERALS
/// approx 5 literals per clause; 64 bytes = 32 literals => 300 cache lines
[[maybe_unused]] constexpr auto SLS_MAX_CNF_LITERALS = SLS_MAX_CLAUSES * stl::Size(5);
#else
[[maybe_unused]] constexpr auto SLS_MAX_CNF_LITERALS = stl::Size(SLS_OPTION_MAX_CNF_LITERALS);
#endif

[[maybe_unused]] [[nodiscard]] constexpr inline literal_type
Lit(variable_type var, stl::i8_type sign) noexcept
{
  stl::Assert(var < SLS_MAX_VARIABLES, "Invalid Variable passed!");
  auto literal = static_cast<literal_type>((var << 1) | sign);
  return literal;
}

}

#endif
