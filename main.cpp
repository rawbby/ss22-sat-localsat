#include <stl/allocator/allocator.hpp>

int
main()
{
  auto allocator = stl::HeapAllocator();
  auto memory = allocator.Allocate<int>(5);

  return 0;
}
