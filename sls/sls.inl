#ifndef SLS_SLS_INL
#define SLS_SLS_INL

#include "sls.hpp"

namespace sls {
using namespace stl;

[[maybe_unused]] inline assignment_type
SLS(const cnf_type* cnf) noexcept
{
  assignment_type result;

  volatile bool found = false;

  omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel
  {
    auto id = omp_get_thread_num();
    auto random = Random(id);
    assignment_type assign;

    do {
      assign = Assignment(cnf, &random);

      const auto n = I32(cnf->num_variables) + I32(cnf->num_clauses);
      for (auto i = I32(0); (!found && i < n); ++i) {

        assign.BestFlip(cnf, &random);
        // assign.BestFlip(cnf);

        if (!assign.Score()) {
#pragma omp critical
          {
            found = true;
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
