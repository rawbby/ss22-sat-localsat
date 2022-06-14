#ifndef STL_UTIL_HPP
#define STL_UTIL_HPP

#include <stdexcept>   // std::logic_error
#include <type_traits> // std::is_constant_evaluated
#include <utility>     // std::swap

#include "def.hpp"
#include "sys.hpp" // Put, Exit

// TODO: DebugBreak is a nice utility but
//       it pollutes the global namespace

#ifdef WIN32
#include <windows.h> // DebugBreak()
#else
#define DebugBreak() ((void)0)
#endif

namespace stl {

namespace detail {

/**
 * This method is placed after a failed assert and will force
 * a constexpr context to fail immediately. This is nicer than
 * failing through another non constexpr function due to its more
 * meaningful name.
 *
 * In a non constexpr context it will
 * be optimized away by the compiler.
 */
[[maybe_unused]] inline void
EXPANDING_CONSTANT_EXPRESSION_FAILED() noexcept
{
}

}

template<typename type_type>
[[maybe_unused]] constexpr inline void
Swap(type_type* a, type_type* b) noexcept
{
  std::swap(a, b);
}

[[maybe_unused]] constexpr inline void
Assert(bool_type condition, const char_type* message) noexcept
{
#ifndef NDEBUG
  if (condition)
    return;

  detail::EXPANDING_CONSTANT_EXPRESSION_FAILED();
  Put(message);
  DebugBreak();
  Exit(1);
#endif
}

}

#endif
