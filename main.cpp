#include <concepts>
#include <type_traits>

#include <stl/allocator/memory.hpp>
#include <stl/def.hpp>

// clang-format off
template<typename allocator_type>
concept allocator_concept =
                            requires() {
                              { allocator_type{} } -> std::same_as<allocator_type>;
                              { allocator_type{}.Allocate(stl::Size(0)) } -> std::same_as<stl::memory_type>;
                              { allocator_type{}.ReAllocate(stl::memory_type{}, stl::Size(0)) } -> std::same_as<stl::memory_type>;
                              { allocator_type{}.Free(stl::memory_type{}) } -> std::same_as<void>;
                            };
// clang-format on

struct test
{
  test() = default;
  stl::memory_type Allocate(stl::size_type) { return {}; }
  stl::memory_type ReAllocate(stl::memory_type, stl::size_type) { return {}; }
  void Free(stl::memory_type) { return; }
};

static_assert(allocator_concept<test>);

int
main()
{
  return 0;
}
