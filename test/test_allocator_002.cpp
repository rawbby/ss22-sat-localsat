#include "test_util.hpp"

#include <stl/allocator/allocator.hpp>

struct data_type
{
  stl::byte_type data[0x1000];
};

#define InStack(stack, p) ((((void*)(stack).data.begin()) <= ((void*)(p))) && (((void*)(p)) < ((void*)(stack).data.end())))

int
main()
{
  using stack_alloc_t = stl::stack_allocator_type<0x4000, stl::alignment_cache_line_tag>;
  using heap_alloc_t = stl::heap_allocator_type<stl::alignment_cache_line_tag>;
  using fallback_alloc_t = stl::fallback_allocator_type<stack_alloc_t, heap_alloc_t>;

  auto alloc = fallback_alloc_t();

  auto heap_memory_0 = alloc.Allocate<data_type>(16);
  auto stack_memory_0 = alloc.Allocate<data_type>(2);
  auto heap_memory_1 = alloc.Allocate<data_type>(3);
  auto stack_memory_1 = alloc.Allocate<data_type>(1);
  auto stack_memory_2 = alloc.Allocate<data_type>(1);
  auto heap_memory_2 = alloc.Allocate<data_type>(1);

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

  alloc.Free<data_type>(heap_memory_2);
  alloc.Free<data_type>(stack_memory_2);
  alloc.Free<data_type>(stack_memory_1);
  alloc.Free<data_type>(heap_memory_1);
  alloc.Free<data_type>(stack_memory_0);
  alloc.Free<data_type>(heap_memory_0);
}
