#ifndef SLS_ASSIGNMENT_HPP
#define SLS_ASSIGNMENT_HPP

#include <stl/dynamic_array.hpp>
#include <stl/random.hpp>
#include <stl/static_vector.hpp>
#include <stl/view.hpp>

#include "cnf.hpp"
#include "def.hpp"

namespace sls {

struct assignment_type
{
#ifdef SLS_STATIC_ASSIGNMENT
  stl::static_vector_type<stl::b8_type, SLS_MAX_VARIABLES> assign;
  stl::static_vector_type<stl::size_type, SLS_MAX_CLAUSES> satisfied_counts;
#else
  stl::heap_allocator_type<stl::alignment_cache_line_tag> allocator;
  stl::dynamic_array_type<stl::b8_type, decltype(allocator)> assign;
  stl::dynamic_array_type<stl::b8_type, decltype(allocator)> satisfied_counts;
#endif

  stl::size_type loop_offset;

  MI assignment_type(stl::size_type num_variables)
    : allocator()
    , assign(&allocator, num_variables)
    , satisfied_counts(&allocator, num_variables << 1)
    , loop_offset(0)
  {
  }

  MI void Flip(const cnf_type* cnf, variable_type variable) noexcept;
  MI void RandomFlip(const cnf_type* cnf, stl::random_type random) noexcept;
  MI void BestFlip(const cnf_type* cnf) noexcept;
  MI void BestFlip(const cnf_type* cnf, stl::random_type* random) noexcept;
  MI void RandomReset(const cnf_type* cnf, stl::random_type* random) noexcept;
  MI void UpdateStats(const cnf_type* cnf) noexcept;
  MNI float Score() noexcept;
  MNI stl::size_type FlipStat(const cnf_type* cnf, variable_type variable) noexcept;

  // === iterator support ===
  MNI stl::i8_type* begin() noexcept;
  MNI stl::i8_type* end() noexcept;
};

MI void
Assignment(assignment_type* assign, const cnf_type* cnf) noexcept;

MNI assignment_type
Assignment(const cnf_type* cnf) noexcept;

MI void
Assignment(assignment_type* assign, const cnf_type* cnf, stl::random_type* random) noexcept;

MNI assignment_type
Assignment(const cnf_type* cnf, stl::random_type* random) noexcept;

}

// include implementation
#include "assignment.inl"

#endif
