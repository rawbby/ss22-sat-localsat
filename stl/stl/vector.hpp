#ifndef STL_VECTOR_HPP
#define STL_VECTOR_HPP

#include "def.hpp"
#include <concepts>
#include <type_traits>

namespace stl {

// clang-format off
template<typename vector_type, typename type_type>
concept vector_concept =
                            requires(vector_type vector) {
                              { vector.Count() } -> std::same_as<stl::size_type>;
                              { vector.Count(Size(0)) } -> std::same_as<void>;
                              { vector.At(Size(0)) } -> std::same_as<type_type*>;
                            } &&
                            requires(const vector_type vector) {
                              { vector.Count() } -> std::same_as<stl::size_type>;
                              { vector.At(Size(0)) } -> std::same_as<const type_type*>;
                            };
// clang-format on

}

#endif
