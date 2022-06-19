#ifndef SLS_ASSIGNMENT_HPP
#define SLS_ASSIGNMENT_HPP

#include <stl/dynamic_array.hpp>
#include <stl/random.hpp>
#include <stl/static_vector.hpp>
#include <stl/view.hpp>

#include "cnf.hpp"
#include "def.hpp"

namespace sls {

template<typename allocator_type>
struct assignment_type
{
  allocator_type* allocator;
  stl::dynamic_array_type<stl::b8_type, allocator_type> assign;
  stl::dynamic_array_type<stl::size_type, allocator_type> satisfied_counts;

  stl::size_type loop_offset;

  MI assignment_type(allocator_type* allocator, stl::size_type num_variables, stl::size_type num_clauses)
    : allocator(allocator)
    , assign(allocator, num_variables)
    , satisfied_counts(allocator, num_clauses)
    , loop_offset(0)
  {
  }

  MI assignment_type(assignment_type&& assignment)
    : allocator(nullptr)
    , assign(nullptr, 0)
    , satisfied_counts(nullptr, 0)
    , loop_offset(0)
  {
    *this = std::move(assignment);
  }

  MI assignment_type& operator=(assignment_type&& other)
  {
    std::swap(allocator, other.allocator);
    std::swap(assign, other.assign);
    std::swap(satisfied_counts, other.satisfied_counts);
    std::swap(loop_offset, other.loop_offset);
    return *this;
  }

  template<typename other_allocator_type>
  MI assignment_type& operator=(const assignment_type<other_allocator_type>& other)
  {
    memcpy(assign.data.data, other.assign.data.data, other.assign.data.count * sizeof(stl::b8_type));
    memcpy(satisfied_counts.data.data, other.satisfied_counts.data.data, other.satisfied_counts.data.count * sizeof(stl::size_type));
    return *this;
  }

  template<typename cnf_allocator_type>
  MI void Flip(const cnf_type<cnf_allocator_type>* cnf, variable_type variable) noexcept;
  template<typename cnf_allocator_type>
  MI void RandomFlip(const cnf_type<cnf_allocator_type>* cnf, stl::random_type random) noexcept;
  template<typename cnf_allocator_type>
  MI void BestFlip(const cnf_type<cnf_allocator_type>* cnf) noexcept;
  template<typename cnf_allocator_type>
  MI void BestFlip(const cnf_type<cnf_allocator_type>* cnf, stl::random_type* random) noexcept;
  template<typename cnf_allocator_type>
  MI void RandomReset(const cnf_type<cnf_allocator_type>* cnf, stl::random_type* random) noexcept;
  template<typename cnf_allocator_type>
  MI void UpdateStats(const cnf_type<cnf_allocator_type>* cnf) noexcept;
  MNI float Score() noexcept;
  template<typename cnf_allocator_type>
  MNI stl::size_type FlipStat(const cnf_type<cnf_allocator_type>* cnf, variable_type variable) noexcept;

  // === iterator support ===
  MNI stl::i8_type* begin() noexcept;
  MNI stl::i8_type* end() noexcept;
};

}

// include implementation
#include "assignment.inl"

#endif
