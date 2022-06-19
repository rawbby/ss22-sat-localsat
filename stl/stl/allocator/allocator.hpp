#ifndef STL_ALLOCATOR_HPP
#define STL_ALLOCATOR_HPP

#include "../def.hpp"

#include "alignment.hpp"
#include "memory.hpp"

#include <concepts>
#include <type_traits>

namespace stl {

template<typename allocator_type>
concept allocator_concept = (
  // clang-format off
  requires(allocator_type allocator, memory_type<> memory) {
    { allocator_type{} } -> std::same_as<allocator_type>;
    { allocator.template Allocate<>(Size(0)) } -> std::same_as<memory_type<>>;
    { allocator.template ReAllocate<>(memory, Size(0)) } -> std::same_as<memory_type<>>;
    { allocator.template Free<>(memory) } -> std::same_as<void>;
  }
  // clang-format on
);

template<typename allocator_type>
concept owning_allocator_concept = (
  // clang-format off
  allocator_concept<allocator_type> &&
  requires(allocator_type allocator, memory_type<> memory) {
    { allocator.template Owns<>(memory) } -> std::same_as<bool_type>;
  }
  // clang-format on
);

}

// basic allocators
#include "heap_allocator.hpp"
#include "stack_allocator.hpp"

// composing allocators
#include "fallback_allocator.hpp"
#include "segregator.hpp"

#endif
