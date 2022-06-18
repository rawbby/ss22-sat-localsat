#ifndef STL_ALIGNMENT_HPP
#define STL_ALIGNMENT_HPP

#include "../def.hpp"

#include <bit>
#include <cstring>

namespace stl {

template<size_type bytes>
struct alignment_bytes_tag
{
  static_assert(std::popcount(U64(bytes)) == 1, "Template Parameter `bytes` must be 2^n.");
  MCI static auto alignment = U64(bytes);
  MCI static auto lo_mask = U64(alignment - U64(1));
  MCI static auto hi_mask = U64(~lo_mask);

  MNI static u64_type align(u64_type address)
  {
    // Add 1 alignment to address
    // if there are bit at lo_mask.
    address += (address & lo_mask) ? alignment : 0;
    return address & hi_mask;
  }

  template<typename type_type>
  MNI static type_type* align(type_type* pointer)
  {
    // Notice: memcpy is the safest way for
    // manipulating pointers at bit level.
    // There is nothing unefficient to this
    // idiom. The compiler understands it well.
    const auto address = align(U64(pointer));
    std::memcpy(&pointer, &address, sizeof(pointer));
    return pointer;
  }
};

struct alignment_no_tag
{
  MCI static auto alignment = U64(1);
  MCI static auto lo_mask = U64(0);
  MCI static auto hi_mask = U64(~lo_mask);

  MNI static u64_type align(u64_type address) { return address; }

  template<typename type_type>
  MNI static type_type* align(type_type* pointer)
  {
    return pointer;
  }
};

typedef alignment_bytes_tag<0x0008> alignment_8_byte_tag;
typedef alignment_bytes_tag<0x0040> alignment_cache_line_tag;
typedef alignment_bytes_tag<0x4000> alignment_page_tag;

}

#endif
