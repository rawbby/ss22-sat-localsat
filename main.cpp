#include "stl/stl.hpp"

int
main()
{
  auto allocator = stl::HeapAllocator<stl::alignment_cache_line_tag>();
  auto vector = stl::DynamicVector<stl::size_type>(&allocator);

  vector.Push(stl::Size(0));

  return 0;
}
