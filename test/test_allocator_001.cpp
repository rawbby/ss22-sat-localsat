#include "test_util.hpp"

#include <stl/allocator/allocator.hpp>

int
main()
{
  static_assert(stl::allocator_concept<stl::heap_allocator_type<stl::alignment_no_tag>>);
  static_assert(stl::allocator_concept<stl::heap_allocator_type<stl::alignment_8_byte_tag>>);
  static_assert(stl::allocator_concept<stl::heap_allocator_type<stl::alignment_cache_line_tag>>);
  static_assert(stl::allocator_concept<stl::heap_allocator_type<stl::alignment_page_tag>>);

  static_assert(stl::allocator_concept<stl::stack_allocator_type<0x1000, stl::alignment_no_tag>>);
  static_assert(stl::allocator_concept<stl::stack_allocator_type<0x1000, stl::alignment_8_byte_tag>>);
  static_assert(stl::allocator_concept<stl::stack_allocator_type<0x1000, stl::alignment_cache_line_tag>>);
  static_assert(stl::allocator_concept<stl::stack_allocator_type<0x1000, stl::alignment_page_tag>>);

  using simple_stack_allocator_type = stl::stack_allocator_type<0x1000, stl::alignment_8_byte_tag>;
  using simple_heap_allocator_type = stl::heap_allocator_type<stl::alignment_cache_line_tag>;
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, simple_stack_allocator_type, simple_heap_allocator_type>>);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<simple_stack_allocator_type, simple_heap_allocator_type>>);
}
