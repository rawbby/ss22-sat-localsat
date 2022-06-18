#include <stl/allocator/allocator.hpp>

int
main()
{
  auto allocator = stl::heap_allocator_type();
  auto memory = allocator.Allocate<int>(5);

  return 0;
}
