#ifndef SLS_SLS_INL
#define SLS_SLS_INL

#include "sls.hpp"

namespace sls {

template<typename allocator_type>
MI void
SLS(assignment_type<allocator_type>* result, const cnf_type<allocator_type>* cnf) noexcept
{
  volatile bool found = false;

  omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel default(none) shared(cnf, found, result)
  {
    auto id = omp_get_thread_num();
    auto random = stl::Random(id);

    stl::fallback_allocator_type<stl::stack_allocator_type<0x4000, stl::alignment_page_tag>,
                                 stl::heap_allocator_type<stl::alignment_cache_line_tag>>
      allocator;

    assignment_type assign{ &allocator, cnf->num_variables, cnf->num_clauses };

    do {
      assign.RandomReset(cnf, &random);

      const auto n = (stl::I32(cnf->num_variables) + stl::I32(cnf->num_clauses)) << 1;
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

template<typename allocator_type>
MI assignment_type<allocator_type>
SLS(allocator_type* allocator, const cnf_type<allocator_type>* cnf) noexcept
{
  assignment_type<allocator_type> result{ allocator, 0, 0 };
  SLS(&result, cnf);
  return result;
}

}

#endif
