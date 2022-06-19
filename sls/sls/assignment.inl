#ifndef SLS_ASSIGNMENT_INL
#define SLS_ASSIGNMENT_INL

#include "assignment.hpp"

#include <stl/range.hpp>

namespace sls {

//  __  __   _____   _____   _   _    ___    ____    ____
// |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
// | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
// | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
// |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

template<typename allocator_type>
template<typename cnf_allocator_type>
MI void
assignment_type<allocator_type>::Flip(const cnf_type<cnf_allocator_type>* cnf, variable_type variable) noexcept
{
  const auto sign = stl::Not(assign[variable]);

  const auto pos_literal = Lit(variable, sign);
  for (auto clause_index : cnf->ResolvingClauses(pos_literal))
    ++satisfied_counts[clause_index];

  const auto neg_literal = Lit(variable, stl::Not(sign));
  for (auto clause_index : cnf->ResolvingClauses(neg_literal))
    --satisfied_counts[clause_index];
}

template<typename allocator_type>
template<typename cnf_allocator_type>
MI void
assignment_type<allocator_type>::RandomFlip(const cnf_type<cnf_allocator_type>* cnf, stl::random_type random) noexcept
{
  Flip(cnf, Var(random.RandInt(cnf->num_variables)));
}

template<typename allocator_type>
template<typename cnf_allocator_type>
MI void
assignment_type<allocator_type>::BestFlip(const cnf_type<cnf_allocator_type>* cnf) noexcept
{
  // use loop_offset to start at new position
  // so less loops occur. this seems to be
  // very important! random seems to be more
  // efficient than loop_offset but tests are
  // required to prove.

  ++loop_offset;
  loop_offset = loop_offset < cnf->num_variables ? loop_offset : 0;

  auto best_var = Var(0);
  auto best_stat = FlipStat(cnf, best_var);

  const auto n = Var(loop_offset);
  const auto m = Var(cnf->num_variables);

  for (auto var : stl::Range(n, m)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
    }
  }
  for (auto var : stl::Range(Var(0), n)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
    }
  }

  Flip(cnf, best_var);
}

template<typename allocator_type>
template<typename cnf_allocator_type>
MI void
assignment_type<allocator_type>::BestFlip(const cnf_type<cnf_allocator_type>* cnf, stl::random_type* random) noexcept
{
  // use random to start at new position
  // so less loops occur. this seems to
  // be very important!

  auto best_var = Var(0);
  auto best_stat = FlipStat(cnf, best_var);

  const auto n = Var(random->RandInt(cnf->num_variables));
  const auto m = Var(cnf->num_variables);

  for (auto var : stl::Range(n, m)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
    }
  }
  for (auto var : stl::Range(Var(0), n)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
    }
  }

  Flip(cnf, best_var);
}

template<typename allocator_type>
template<typename cnf_allocator_type>
MI void
assignment_type<allocator_type>::RandomReset(const cnf_type<cnf_allocator_type>* cnf, stl::random_type* random) noexcept
{
  for (auto& sign : assign)
    sign = stl::I8(random->RandBool());

  UpdateStats(cnf);
}

template<typename allocator_type>
template<typename cnf_allocator_type>
MI void
assignment_type<allocator_type>::UpdateStats(const cnf_type<cnf_allocator_type>* cnf) noexcept
{
  satisfied_counts.View().MemSet(stl::I32(0));

  auto variable = Var(0);
  for (auto& sign : assign) {

    auto literal = Lit(variable, sign);

    for (auto clause_index : cnf->ResolvingClauses(literal))
      *satisfied_counts.At(clause_index) += 1;

    ++variable;
  }
}

template<typename allocator_type>
MNI float
assignment_type<allocator_type>::Score() noexcept
{
  auto score = satisfied_counts.Count();
  for (auto count : satisfied_counts)
    score -= count ? 1 : 0;

  return stl::F32(score);
}

template<typename allocator_type>
template<typename cnf_allocator_type>
MNI stl::size_type
assignment_type<allocator_type>::FlipStat(const cnf_type<cnf_allocator_type>* cnf, variable_type variable) noexcept
{
  auto sign = assign[variable];

  auto sat_clauses = cnf->ResolvingClauses(Lit(variable, sign));
  auto unsat_clauses = cnf->ResolvingClauses(Lit(variable, stl::Not(sign)));

  auto stat = stl::Size(0);

  for (auto index : sat_clauses)
    stat -= satisfied_counts[index] == 1 ? 1 : 0;

  for (auto index : unsat_clauses)
    stat += satisfied_counts[index] == 0 ? 1 : 0;

  return stat;
}

template<typename allocator_type>
MNI stl::i8_type*
assignment_type<allocator_type>::begin() noexcept
{
  return assign.begin();
}

template<typename allocator_type>
MNI stl::i8_type*
assignment_type<allocator_type>::end() noexcept
{
  return assign.end();
}

}

#endif
