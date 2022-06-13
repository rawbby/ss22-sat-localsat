#ifndef SLS_SLS_HPP
#define SLS_SLS_HPP

#include <omp.h>
#include <stl/stl.hpp>

#include "assignment.hpp"
#include "cnf.hpp"
#include "def.hpp"

namespace sls {
using namespace stl;

[[maybe_unused]] inline assignment_type
SLS(const cnf_type* cnf);

}

// include implementation
#include "sls.inl"

#endif
