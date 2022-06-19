#ifndef SLS_SLS_INL
#define SLS_SLS_INL

#include "sls.hpp"

namespace sls {

MI void
SLS(assignment_type* result, const cnf_type* cnf) noexcept
{
  volatile bool found = false;

  omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel default(none) shared(cnf, found, result)
  {
    auto id = omp_get_thread_num();
    auto random = stl::Random(id);

    assignment_type assign{ cnf->num_variables };

    do {
      Assignment(&assign, cnf, &random);

      const auto n = stl::I32(cnf->num_variables) + stl::I32(cnf->num_clauses);
      for (auto i = stl::I32(0); (!found && i < n); ++i) {

        assign.BestFlip(cnf, &random);
        // assign.BestFlip(cnf);

        [[unlikely]] if (!assign.Score())
        {
#pragma omp critical
          {
            found = true;
            *result = std::move(assign);
          }
          break;
        }
      }
    } while (!found);

#ifdef SLS_OPTION_ALLOCATE_HEAP
#ifndef SLS_OPTION_NO_FREE
    free(assign);
#endif
#endif
  }
}

MI assignment_type
SLS(const cnf_type* cnf) noexcept
{
  assignment_type result{ cnf->num_variables };
  SLS(&result, cnf);
  return result;
}

}

#endif
