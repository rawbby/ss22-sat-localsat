#ifndef SLS_SLS_HPP
#define SLS_SLS_HPP

#include <stl/stl.hpp>
#include <omp.h>

#include "def.hpp"
#include "cnf.hpp"
#include "assignment.hpp"

namespace sls {
using namespace stl;

[[maybe_unused]] inline assignment_type
SLS(const cnf_type* cnf);

}

// include implementation
#include "sls.inl"

#endif
