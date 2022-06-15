#ifndef STL_DEF_HPP
#define STL_DEF_HPP

#include <cstdint>
#include <type_traits> // std::is_integral, std::is_floating_point

namespace stl {

#ifndef NDEBUG
#define STL_OPTION_DEBUG
#endif

#define STL_DEFINE_INTEGRAL_CONSTRUCTOR(base_type, integral_type, name)                                                                        \
  typedef base_type integral_type;                                                                                                             \
  static_assert(std::is_integral<integral_type>::value, "defined ill formed integral type " #integral_type ".");                               \
                                                                                                                                               \
  template<typename type_type>                                                                                                                 \
  [[maybe_unused]] [[nodiscard]] constexpr inline integral_type name(type_type type) noexcept                                                  \
  {                                                                                                                                            \
    return static_cast<integral_type>(type);                                                                                                   \
  }

#define STL_DEFINE_FLOATING_CONSTRUCTOR(base_type, floating_point_type, name)                                                                  \
  typedef base_type floating_point_type;                                                                                                       \
  static_assert(std::is_floating_point<floating_point_type>::value, "defined ill formed floating point type " #floating_point_type ".");       \
                                                                                                                                               \
  template<typename type_type>                                                                                                                 \
  [[maybe_unused]] [[nodiscard]] constexpr inline floating_point_type name(type_type type) noexcept                                            \
  {                                                                                                                                            \
    return static_cast<floating_point_type>(type);                                                                                             \
  }

STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::int8_t, i8_type, I8)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::int16_t, i16_type, I16)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::int32_t, i32_type, I32)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::int64_t, i64_type, I64)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::uint8_t, u8_type, U8)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::uint16_t, u16_type, U16)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::uint32_t, u32_type, U32)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::uint64_t, u64_type, U64)
STL_DEFINE_FLOATING_CONSTRUCTOR(float, f32_type, F32)
STL_DEFINE_FLOATING_CONSTRUCTOR(double, f64_type, F64)

STL_DEFINE_INTEGRAL_CONSTRUCTOR(bool, bool_type, Bool)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(char, char_type, Char)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(i32_type, size_type, Size)

}

#endif
