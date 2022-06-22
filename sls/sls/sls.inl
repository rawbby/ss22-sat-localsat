#ifndef SLS_SLS_INL
#define SLS_SLS_INL

#include "sls.hpp"

namespace sls {

MI void
SLS(assignment_type<decltype(global_allocator)>* result, const cnf_type* cnf) noexcept
{
  volatile bool found = false;

  omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel default(none) shared(cnf, found, result)
  {
    auto id = omp_get_thread_num();
    auto random = stl::Random(id);

    auto allocator = CreateThreadLocalAllocator();
    assignment_type assign{ &allocator, cnf->num_variables, cnf->num_clauses };

    do {
      assign.RandomReset(cnf, &random);

      const auto n = (stl::I32(cnf->num_variables) << 1) + (stl::I32(cnf->num_clauses) >> 3);
      for (auto i = stl::I32(0); !found && i < n; ++i) {

        // assign.FirstGoodFlip(cnf, &random);
        assign.BestFlip(cnf, &random);

        [[unlikely]] if (!assign.Score())
        {
#pragma omp critical
          {
            found = true;

            // *result = assign;
            // TODO find a more idiomatic copy
            memcpy(result->assign.data.data, assign.assign.data.data, assign.assign.data.count * sizeof(stl::b8_type));
            memcpy(result->satisfied_counts.data.data,
                   assign.satisfied_counts.data.data,
                   assign.satisfied_counts.data.count * sizeof(stl::size_type));
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
