#ifndef SLS_SLS_INL
#define SLS_SLS_INL

#include "sls.hpp"
#include <iostream>

namespace sls {

MI void
SLS(assignment_type<decltype(global_allocator)>* result, const cnf_type* cnf) noexcept
{
  volatile bool found = false;

  omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel default(none) shared(cnf, found, result, std::cout)
  {
    auto id = omp_get_thread_num();
    auto random = stl::Random(id);

    auto allocator = CreateThreadLocalAllocator();
    assignment_type assign{ &allocator, cnf->num_variables, cnf->num_clauses };

    do {
      assign.RandomReset(cnf, &random);

      const auto n = stl::I32(cnf->num_variables) + stl::I32(cnf->num_clauses);
      for (auto i = stl::I32(0); (!found && i < n); ++i) {

        assign.BestFlip(cnf, &random);

        [[unlikely]] if (!assign.Score())
        {
#pragma omp critical
          {
            found = true;
            *result = assign;
          }
          break;
        }
      }
    } while (!found);
  }
}

MI assignment_type<decltype(global_allocator)>
SLS(const cnf_type* cnf) noexcept
{
  assignment_type<decltype(global_allocator)> result{ &global_allocator, cnf->num_variables, cnf->num_clauses };
  SLS(&result, cnf);
  return result;
}

}

#endif
