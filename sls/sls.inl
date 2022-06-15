#ifndef SLS_SLS_INL
#define SLS_SLS_INL

#include "sls.hpp"

namespace sls {
using namespace stl;

[[maybe_unused]] inline void
SLS(assignment_type* result, const cnf_type* cnf) noexcept
{
  volatile bool found = false;

  omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel default(none) shared(cnf, found, result)
  {
    auto id = omp_get_thread_num();
    auto random = Random(id);

#ifndef OPTION_ALLOCATE_HEAP
    assignment_type assign_;
    assignment_type* assign = &assign_;
#else
    assignment_type* assign = static_cast<assignment_type*>(malloc(sizeof(assignment_type)));
#endif

    do {
      Assignment(assign, cnf, &random);

      const auto n = I32(cnf->num_variables) + I32(cnf->num_clauses);
      for (auto i = I32(0); (!found && i < n); ++i) {

        assign->BestFlip(cnf, &random);
        // assign.BestFlip(cnf);

        [[unlikely]] if (!assign->Score()) {
#pragma omp critical
          {
            found = true;
            std::swap(*result, *assign);
          }
          break;
        }
      }
    } while (!found);

#ifdef OPTION_ALLOCATE_HEAP
#ifndef OPTION_NO_FREE
    free(assign);
#endif
#endif
  }
}

[[maybe_unused]] inline assignment_type
SLS(const cnf_type* cnf) noexcept
{
  assignment_type result;
  SLS(&result, cnf);
  return result;
}

}

#endif
