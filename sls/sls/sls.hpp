#ifndef SLS_SLS_HPP
#define SLS_SLS_HPP

#include <omp.h>
#include <stl/stl.hpp>

#include "assignment.hpp"
#include "cnf.hpp"
#include "def.hpp"

namespace sls {

template<typename allocator_type>
MI void
SLS(assignment_type<allocator_type>* assignment, const cnf_type<allocator_type>* cnf) noexcept;

template<typename allocator_type>
MI assignment_type<allocator_type>
SLS(allocator_type* allocator, const cnf_type<allocator_type>* cnf) noexcept;

}

// include implementation
#include "sls.inl"

#endif
