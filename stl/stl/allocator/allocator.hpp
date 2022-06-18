#ifndef STL_ALLOCATOR_HPP
#define STL_ALLOCATOR_HPP

#include "../def.hpp"
#include "memory.hpp"

#include <concepts>
#include <type_traits>

namespace stl {

template<typename allocator_type, typename type_type = byte_type>
concept allocator_concept = (
  // clang-format off
  requires(allocator_type allocator) {
    { allocator_type{} } -> std::same_as<allocator_type>;
    { allocator.template Allocate<type_type>(Size(0)) } -> std::same_as<memory_type<type_type>>;
    { allocator.template ReAllocate<type_type>(memory_type{}, Size(0)) } -> std::same_as<memory_type<type_type>>;
    { allocator.template Free<type_type>(memory_type{}) } -> std::same_as<void>;
  }
  // clang-format on
);

template<typename allocator_type, typename type_type = byte_type>
concept owning_allocator_concept = (
  // clang-format off
  allocator_concept<allocator_type> &&
  requires(allocator_type allocator) {
    { allocator.Owns(memory_type<type_type>{}) } -> std::same_as<bool_type>;
  }
  // clang-format on
);

}

#include "fallback_allocator.hpp"
#include "heap_allocator.hpp"
#include "segregator.hpp"
#include "stack_allocator.hpp"

#endif
