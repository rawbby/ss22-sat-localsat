#include "test_util.hpp"

#include <stl/allocator/allocator.hpp>

#define InStack(stack, p) ((((void*)(stack).data.begin()) <= ((void*)(p))) && (((void*)(p)) < ((void*)(stack).data.end())))

using type_type = stl::byte_type[0x1000];

void
test_allocator_requirements()
{
#define E_MSG " Allocator Concept not fulfilled!"

  using halloc0 = stl::heap_allocator_type<stl::alignment_no_tag>;
  using halloc1 = stl::heap_allocator_type<stl::alignment_8_byte_tag>;
  using halloc2 = stl::heap_allocator_type<stl::alignment_cache_line_tag>;
  using halloc3 = stl::heap_allocator_type<stl::alignment_page_tag>;

  using salloc0 = stl::stack_allocator_type<0x1000, stl::alignment_no_tag>;
  using salloc1 = stl::stack_allocator_type<0x1000, stl::alignment_8_byte_tag>;
  using salloc2 = stl::stack_allocator_type<0x1000, stl::alignment_cache_line_tag>;
  using salloc3 = stl::stack_allocator_type<0x1000, stl::alignment_page_tag>;

  static_assert(stl::allocator_concept<halloc0>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<halloc1>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<halloc2>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<halloc3>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<salloc0>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<salloc1>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<salloc2>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<salloc3>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc0, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc0, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc0, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc0, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc0, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc0, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc0, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc1, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc1, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc1, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc1, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc1, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc1, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc1, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc2, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc2, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc2, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc2, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc2, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc2, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc2, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc3, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc3, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc3, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc3, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc3, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc3, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, halloc3, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc0, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc0, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc0, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc0, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc0, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc0, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc0, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc1, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc1, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc1, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc1, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc1, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc1, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc1, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc2, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc2, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc2, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc2, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc2, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc2, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc2, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc3, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc3, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc3, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc3, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc3, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc3, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::segregator_type<0x1000, salloc3, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc0, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc0, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc0, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc0, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc0, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc0, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc0, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc1, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc1, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc1, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc1, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc1, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc1, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc1, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc2, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc2, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc2, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc2, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc2, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc2, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc2, salloc3>>, TEST_FAILURE_MESSAGE() E_MSG);

  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc3, halloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc3, halloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc3, halloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc3, halloc3>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc3, salloc0>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc3, salloc1>>, TEST_FAILURE_MESSAGE() E_MSG);
  static_assert(stl::allocator_concept<stl::fallback_allocator_type<salloc3, salloc2>>, TEST_FAILURE_MESSAGE() E_MSG);
}

void
test_heap_allocator_alignment()
{
  auto allocator = stl::heap_allocator_type<stl::alignment_cache_line_tag>();

  auto memory0 = allocator.Allocate(0x1000);
  stl::Assert(memory0.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory0.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory1 = allocator.Allocate(0x1000);
  stl::Assert(memory1.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory1.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory2 = allocator.Allocate(0x1000);
  stl::Assert(memory2.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory2.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory3 = allocator.ReAllocate(memory2, 0x2000);
  stl::Assert(memory3.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory3.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  allocator.Free(memory0);
  allocator.Free(memory1);
  allocator.Free(memory3);
}

void
test_stack_allocator_alignment()
{
  auto allocator = stl::stack_allocator_type<0x4000, stl::alignment_cache_line_tag>();

  auto memory0 = allocator.Allocate(0x1000);
  stl::Assert(memory0.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory0.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory1 = allocator.Allocate(0x1000);
  stl::Assert(memory1.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory1.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory2 = allocator.Allocate(0x1000);
  stl::Assert(memory2.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory2.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory3 = allocator.ReAllocate(memory2, 0x2000);
  stl::Assert(memory3.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(!(stl::U64(memory3.data) & stl::alignment_cache_line_tag::lo_mask), TEST_FAILURE_MESSAGE());

  auto memory4 = allocator.Allocate(0x1000);
  stl::Assert(!memory4.data, TEST_FAILURE_MESSAGE());
  stl::Assert(!memory4.count, TEST_FAILURE_MESSAGE());

  allocator.Free(memory3);
  allocator.Free(memory1);
  allocator.Free(memory0);
}

void
test_fallback_allocator()
{
  using stack_alloc_t = stl::stack_allocator_type<0x4000, stl::alignment_cache_line_tag>;
  using heap_alloc_t = stl::heap_allocator_type<stl::alignment_cache_line_tag>;
  using fallback_alloc_t = stl::fallback_allocator_type<stack_alloc_t, heap_alloc_t>;
  auto alloc = fallback_alloc_t();

  auto heap_memory_0 = alloc.Allocate<type_type>(16);
  auto stack_memory_0 = alloc.Allocate<type_type>(2);
  auto heap_memory_1 = alloc.Allocate<type_type>(3);
  auto stack_memory_1 = alloc.Allocate<type_type>(1);
  auto stack_memory_2 = alloc.Allocate<type_type>(1);
  auto heap_memory_2 = alloc.Allocate<type_type>(1);

  stl::Assert(heap_memory_0.data, TEST_FAILURE_MESSAGE() " Memory allocation failed!");
  stl::Assert(stack_memory_0.data, TEST_FAILURE_MESSAGE() " Memory allocation failed!");
  stl::Assert(heap_memory_1.data, TEST_FAILURE_MESSAGE() " Memory allocation failed!");
  stl::Assert(stack_memory_1.data, TEST_FAILURE_MESSAGE() " Memory allocation failed!");
  stl::Assert(stack_memory_2.data, TEST_FAILURE_MESSAGE() " Memory allocation failed!");
  stl::Assert(heap_memory_2.data, TEST_FAILURE_MESSAGE() " Memory allocation failed!");

  stl::Assert(!InStack(alloc, heap_memory_0.data), TEST_FAILURE_MESSAGE() " Memory allocated in unexpected Memory Region!");
  stl::Assert(InStack(alloc, stack_memory_0.data), TEST_FAILURE_MESSAGE() " Memory allocated in unexpected Memory Region!");
  stl::Assert(!InStack(alloc, heap_memory_1.data), TEST_FAILURE_MESSAGE() " Memory allocated in unexpected Memory Region!");
  stl::Assert(InStack(alloc, stack_memory_1.data), TEST_FAILURE_MESSAGE() " Memory allocated in unexpected Memory Region!");
  stl::Assert(InStack(alloc, stack_memory_2.data), TEST_FAILURE_MESSAGE() " Memory allocated in unexpected Memory Region!");
  stl::Assert(!InStack(alloc, heap_memory_2.data), TEST_FAILURE_MESSAGE() " Memory allocated in unexpected Memory Region!");

  alloc.Free(heap_memory_2);
  alloc.Free(stack_memory_2);
  alloc.Free(stack_memory_1);
  alloc.Free(heap_memory_1);
  alloc.Free(stack_memory_0);
  alloc.Free(heap_memory_0);
}

void
test_fallback_allocator_realloc()
{
  using stack_alloc_t = stl::stack_allocator_type<3>;
  using heap_alloc_t = stl::heap_allocator_type<>;
  using fallback_alloc_t = stl::fallback_allocator_type<stack_alloc_t, heap_alloc_t>;

  auto alloc = fallback_alloc_t();

  auto memory = alloc.Allocate<stl::byte_type>(1);
  stl::Assert(memory.data != nullptr, TEST_FAILURE_MESSAGE());
  memory.data[0] = stl::Byte(0);

  memory = alloc.ReAllocate(memory, 2);
  stl::Assert(memory.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(memory.data[0] == stl::Byte(0), TEST_FAILURE_MESSAGE());
  memory.data[1] = stl::Byte(1);

  memory = alloc.ReAllocate(memory, 3);
  stl::Assert(memory.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(memory.data[1] == stl::Byte(1), TEST_FAILURE_MESSAGE());
  memory.data[2] = stl::Byte(2);

  memory = alloc.ReAllocate(memory, 4);
  stl::Assert(memory.data != nullptr, TEST_FAILURE_MESSAGE());
  stl::Assert(memory.data[2] == stl::Byte(2), TEST_FAILURE_MESSAGE());
  memory.data[3] = stl::Byte(3);

  stl::size_type n = 2048;
  for (stl::size_type i = 8; i < n; i <<= 1) {
    memory = alloc.ReAllocate(memory, i);
    stl::Assert(memory.data != nullptr, TEST_FAILURE_MESSAGE());

    const auto i_ = i >> 1;
    stl::Assert(memory.data[i_ - 1] == stl::Byte(i_ - 1), TEST_FAILURE_MESSAGE());
    memory.data[i - 1] = stl::Byte(i - 1);
  }

  stl::Assert(memory.data[0] == stl::Byte(0), TEST_FAILURE_MESSAGE());
  stl::Assert(memory.data[1] == stl::Byte(1), TEST_FAILURE_MESSAGE());
  stl::Assert(memory.data[2] == stl::Byte(2), TEST_FAILURE_MESSAGE());
  for (stl::size_type i = 8; i < n; i <<= 1) {
    const auto i_ = i >> 1;
    stl::Assert(memory.data[i_ - 1] == stl::Byte(i_ - 1), TEST_FAILURE_MESSAGE());
  }

  alloc.Free(memory);
}

int
main()
{
  test_allocator_requirements();
  test_heap_allocator_alignment();
  test_stack_allocator_alignment();
  test_fallback_allocator();
  test_fallback_allocator_realloc();
}
