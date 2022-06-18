#ifndef STL_DEF_HPP
#define STL_DEF_HPP

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace stl {

#ifndef NDEBUG
#define STL_OPTION_DEBUG
#endif

#define STL_DEFINE_INTEGRAL_CONSTRUCTOR(base_type, integral_type, name)                                                                        \
  typedef base_type integral_type;                                                                                                             \
                                                                                                                                               \
  template<typename type_type>                                                                                                                 \
  [[maybe_unused]] [[nodiscard]] constexpr inline integral_type name(type_type type) noexcept                                                  \
  {                                                                                                                                            \
    return static_cast<integral_type>(type);                                                                                                   \
  }

#define STL_DEFINE_FLOATING_CONSTRUCTOR(base_type, floating_point_type, name)                                                                  \
  typedef base_type floating_point_type;                                                                                                       \
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

STL_DEFINE_INTEGRAL_CONSTRUCTOR(std::byte, byte_type, Byte)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(bool, bool_type, Bool)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(i8_type, b8_type, B8)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(char, char_type, Char)
STL_DEFINE_INTEGRAL_CONSTRUCTOR(i32_type, size_type, Size)

template<typename type_type>
[[maybe_unused]] [[nodiscard]] constexpr inline u64_type
U64(type_type* pointer) noexcept
{
  static_assert(sizeof(u64_type) >= sizeof(pointer), "Unexpected Pointer Size. Unable to handle Pointer bigger than 8 Bytes.");
  u64_type address;
  std::memcpy(&address, &pointer, sizeof(pointer));
  return address;
}

[[maybe_unused]] [[nodiscard]] constexpr inline b8_type
Not(b8_type value) noexcept
{
  return value ? B8(0) : B8(1);
}

}

#endif
