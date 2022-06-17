#ifndef STL_VECTOR_STACK_HPP
#define STL_VECTOR_STACK_HPP

#include "../stl.hpp"

#include "../static_vector.hpp"
#include "../view.hpp"

namespace stl {

//  ___   _____   _____   ____       _      _____    ___    ____
// |_ _| |_   _| | ____| |  _ \     / \    |_   _|  / _ \  |  _ \
//  | |    | |   |  _|   | |_) |   / _ \     | |   | | | | | |_) |
//  | |    | |   | |___  |  _ <   / ___ \    | |   | |_| | |  _ <
// |___|   |_|   |_____| |_| \_\ /_/   \_\   |_|    \___/  |_| \_\

template<typename type_type>
struct vector_stack_iter_type
{
  type_type* data;
  size_type* range;

  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type(const vector_stack_iter_type& iter) noexcept
    : data(iter.data)
    , range(iter.range)
  {
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type(type_type* data, size_type* range) noexcept
    : data(data)
    , range(range)
  {
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> operator*() const noexcept
  {
    return View(data, range[0], range[1]);
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> operator*() noexcept { return View(data, range[0], range[1]); }

  [[maybe_unused]] constexpr inline vector_stack_iter_type& operator++() noexcept
  {
    range++;
    return *this;
  }

  [[maybe_unused]] constexpr inline vector_stack_iter_type operator++(int) noexcept { return { data, range++ }; }

  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator==(const vector_stack_iter_type& other) const noexcept
  {
    Assert(data == other.data, "Invalid iterator comparison!");
    return range == other.range;
  };

  [[maybe_unused]] [[nodiscard]] constexpr inline bool operator!=(const vector_stack_iter_type& other) const noexcept
  {
    Assert(data == other.data, "Invalid iterator comparison!");
    return range != other.range;
  };
};

//  ____    _____    ____   _          _      ____       _      _____   ___    ___    _   _
// |  _ \  | ____|  / ___| | |        / \    |  _ \     / \    |_   _| |_ _|  / _ \  | \ | |
// | | | | |  _|   | |     | |       / _ \   | |_) |   / _ \     | |    | |  | | | | |  \| |
// | |_| | | |___  | |___  | |___   / ___ \  |  _ <   / ___ \    | |    | |  | |_| | | |\  |
// |____/  |_____|  \____| |_____| /_/   \_\ |_| \_\ /_/   \_\   |_|   |___|  \___/  |_| \_|

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
struct vector_stack_type
{
  static_vector_type<type_type, buffer_capacity> buffer;
  static_vector_type<size_type, Size(1) + stack_capacity> ranges;

  //  __  __   _____   _____   _   _    ___    ____    ____
  // |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
  // | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
  // | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
  // |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

  [[maybe_unused]] [[nodiscard]] constexpr inline size_type Count() const noexcept { return ranges.Count() - Size(1); }

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type> At(size_type index) const noexcept
  {
    Assert(index >= Size(0), "Stack Can not be access with a negative Index!");
    Assert(index < Count(), "Stack Can not be access with an Index larger its Count!");
    const auto lower = *ranges.At(index);
    const auto upper = *ranges.At(index + Size(1));
    // TODO why is explicit ToView needed?
    return View(buffer.ToView(), lower, upper);
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<type_type> At(size_type index) noexcept
  {
    Assert(index >= Size(0), "Stack Can not be access with a negative Index!");
    Assert(index < Count(), "Stack Can not be access with an Index larger its Count!");
    const auto lower = *ranges.At(index);
    const auto upper = *ranges.At(index + Size(1));
    // TODO why is explicit ToView needed?
    return View(buffer.ToView(), lower, upper);
  }

  [[maybe_unused]] constexpr inline void Push(type_type type) noexcept { buffer.Push(type); }

  [[maybe_unused]] constexpr inline void Push() noexcept { ranges.Push(buffer.Count()); }

  [[maybe_unused]] constexpr inline void Pop() noexcept { ranges.Pop(); }

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>* Peak() const noexcept
  {
    Assert(Count() > Size(0), "Can not peak an empty Stack!");
    const auto lower = ranges.At(ranges.Size() - Size(2));
    const auto upper = ranges.At(ranges.Size() - Size(1));
    return buffer.ToView(lower, upper);
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline view_type<const type_type>* Peak() noexcept
  {
    Assert(Count() > Size(0), "Can not peak an empty Stack!");
    const auto lower = ranges.At(ranges.Count() - Size(2));
    const auto upper = ranges.At(ranges.Count() - Size(1));
    return View(buffer, lower, upper);
  }

  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type<type_type> begin() noexcept { return { buffer.data, ranges.data }; }

  [[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_iter_type<type_type> end() noexcept
  {
    return { buffer.data, &(ranges.data[Count()]) };
  }
};

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] constexpr inline void
VectorStack(vector_stack_type<type_type, stack_capacity, buffer_capacity>* stack) noexcept
{
  StaticVector(&stack->buffer);
  StaticVector(&stack->ranges);
  stack->ranges.Push(Size(0));
}

template<typename type_type, size_type stack_capacity, size_type buffer_capacity>
[[maybe_unused]] [[nodiscard]] constexpr inline vector_stack_type<type_type, stack_capacity, buffer_capacity>
VectorStack() noexcept
{
  vector_stack_type<type_type, stack_capacity, buffer_capacity> stack;
  VectorStack(&stack);
  return stack;
}

}

#endif
