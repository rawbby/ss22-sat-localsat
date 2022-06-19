#ifndef SLS_SLS_HPP
#define SLS_SLS_HPP

#include <omp.h>
#include <stl/stl.hpp>

#include "assignment.hpp"
#include "cnf.hpp"
#include "def.hpp"

namespace sls {

MI void
SLS(assignment_type* assignment, const cnf_type* cnf) noexcept;

MI assignment_type
SLS(const cnf_type* cnf) noexcept;

}

// include implementation
#include "sls.inl"

#endif
