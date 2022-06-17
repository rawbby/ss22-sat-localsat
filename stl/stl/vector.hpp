#ifndef STL_VECTOR_HPP
#define STL_VECTOR_HPP

#include "def.hpp"
#include "view.hpp"
#include <concepts>
#include <type_traits>

namespace stl {

template<typename vector_type, typename type_type>
concept vector_concept = (
  // clang-format off
  viewable_concept<vector_type, type_type> &&
  requires(vector_type vector, type_type type) {
    { vector.Count(Size(0)) } -> std::same_as<void>;
    { vector.Push(type) } -> std::same_as<void>;
    { vector.Pop() } -> std::same_as<void>;
    { vector.Peak() } -> std::same_as<type_type*>;
    { vector.Remove(Size(0)) } -> std::same_as<void>;
  } &&
  requires(const vector_type vector) {
    { vector.Peak() } -> std::same_as<const type_type*>;
  }
  // clang-format on
);

}

#endif
