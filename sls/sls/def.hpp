#ifndef SLS_DEF_HPP
#define SLS_DEF_HPP

#include <stl/random.hpp>
#include <stl/stl.hpp>

namespace sls {

#ifndef SLS_OPTION_STATIC_MEMORY
#ifndef SLS_OPTION_DYNAMIC_MEMORY
#define SLS_OPTION_HYBRID_MEMORY
#endif
#endif

STL_DEFINE_INTEGRAL_CONSTRUCTOR(stl::i16_type, literal_type, Lit)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(stl::i16_type, variable_type, Var)

MNCI literal_type
Lit(variable_type var, stl::i8_type sign) noexcept
{
  auto literal = static_cast<literal_type>((var << 1) | sign);
  return literal;
}

MNCI auto
CreateGlobalAllocator()
{
#if defined(SLS_OPTION_STATIC_MEMORY)
  return stl::stack_allocator_type<0x100000, stl::alignment_cache_line_tag>{};
#elif defined(SLS_OPTION_DYNAMIC_MEMORY)
  return stl::heap_allocator_type<stl::alignment_page_tag>{};
#elif defined(SLS_OPTION_HYBRID_MEMORY)
  using P = stl::stack_allocator_type<0x100000, stl::alignment_cache_line_tag>;
  using S = stl::heap_allocator_type<stl::alignment_page_tag>;
  return stl::fallback_allocator_type<P, S>{};
#endif
}

auto global_allocator = CreateGlobalAllocator();

MNCI auto
CreateThreadLocalAllocator()
{
#if defined(SLS_OPTION_STATIC_MEMORY)
  return stl::stack_allocator_type<0x10000, stl::alignment_cache_line_tag>{};
#elif defined(SLS_OPTION_DYNAMIC_MEMORY)
  return stl::heap_allocator_type<stl::alignment_page_tag>{};
#elif defined(SLS_OPTION_HYBRID_MEMORY)
  using P = stl::stack_allocator_type<0x10000, stl::alignment_cache_line_tag>;
  using S = stl::heap_allocator_type<stl::alignment_page_tag>;
  return stl::fallback_allocator_type<P, S>{};
#endif
}

}

#endif
