#ifndef SLS_SLS_INL
#define SLS_SLS_INL

#include "sls.hpp"

namespace sls {
using namespace stl;

constexpr auto MAX_THREADS = Size(20);

[[maybe_unused]] inline assignment_type
SLS(const cnf_type* cnf)
{
  using namespace detail;

  auto num_threads = Size(omp_get_max_threads());
  num_threads = num_threads > MAX_THREADS ? MAX_THREADS : num_threads;

  assignment_type result;

  volatile bool found = false;

  omp_set_num_threads(num_threads);
#pragma omp parallel
  {
    auto id = omp_get_thread_num();
    auto random = Random(id);
    assignment_type assign;

    do {
      assign = Assignment(cnf, &random);

      const auto n = I32(cnf->num_variables) + I32(cnf->num_clauses);
      for (auto i = I32(0); (!found && i < n); ++i) {
        assign.BestFlip(cnf);
        if (!assign.Score()) {
#pragma omp critical
          {
            found = 1 + id;
            std::swap(result, assign);
          }
          break;
        }
      }
    } while (!found);
  }

  return result;
}

}

#endif
