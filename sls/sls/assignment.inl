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
MI void
assignment_type<allocator_type>::Flip(const cnf_type* cnf, variable_type variable) noexcept
{
  // clauses that may get unsat after flip
  const auto unsat = cnf->ResolvingClauses(Lit(variable, assign[variable]));

  assign[variable] = stl::Not(assign[variable]);

  // clauses that may get sat after flip
  const auto sat = cnf->ResolvingClauses(Lit(variable, assign[variable]));

  for (const auto index : unsat)
    --satisfied_counts[index];

  for (const auto index : sat)
    ++satisfied_counts[index];
}

template<typename allocator_type>
MI void
assignment_type<allocator_type>::RandomFlip(const cnf_type* cnf, stl::random_type random) noexcept
{
  Flip(cnf, Var(random.RandInt(cnf->num_variables)));
}

template<typename allocator_type>
MI void
assignment_type<allocator_type>::BestFlip(const cnf_type* cnf) noexcept
{
  // use loop_offset to start at new position
  // so less loops occur. this seems to be
  // very important! random seems to be more
  // efficient than loop_offset but tests are
  // required to prove.

  ++loop_offset;
  loop_offset = loop_offset < (cnf->num_variables - 1) ? loop_offset : 1;

  const auto n = Var(loop_offset);
  const auto m = Var(cnf->num_variables);

  auto best_var = Var(n);
  auto best_stat = FlipStat(cnf, best_var);

  for (auto var : stl::Range(Var(n + 1), m)) {
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
MI void
assignment_type<allocator_type>::BestFlip(const cnf_type* cnf, stl::random_type* random) noexcept
{
  // use random to start at new position
  // so less loops occur. this seems to
  // be very important!

  // last clause i never chosen for first assign...
  const auto n = Var(random->RandInt(cnf->num_variables));
  const auto m = Var(cnf->num_variables);

  auto best_var = Var(n);
  auto best_stat = FlipStat(cnf, best_var);

  for (auto var : stl::Range(Var(n + 1), m)) {
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
MI void
assignment_type<allocator_type>::FirstGoodFlip(const cnf_type* cnf, stl::random_type* random) noexcept
{
  // use random to start at new position
  // so less loops occur. this seems to
  // be very important!

  // last clause i never chosen for first assign...
  const auto n = Var(random->RandInt(cnf->num_variables));
  const auto m = Var(cnf->num_variables);

  auto best_var = Var(n);
  auto best_stat = FlipStat(cnf, best_var);

  for (auto var : stl::Range(Var(n + 1), m)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
      if (stat > 0) {
        Flip(cnf, best_var);
        return;
      }
    }
  }
  for (auto var : stl::Range(Var(0), n)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
      if (stat > 0) {
        Flip(cnf, best_var);
        return;
      }
    }
  }

  Flip(cnf, best_var);
}

template<typename allocator_type>
MI void
assignment_type<allocator_type>::RandomReset(const cnf_type* cnf, stl::random_type* random) noexcept
{
  for (auto& sign : assign)
    sign = stl::I8(random->RandBool());

  UpdateStats(cnf);
}

template<typename allocator_type>
MI void
assignment_type<allocator_type>::UpdateStats(const cnf_type* cnf) noexcept
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
MNI stl::size_type
assignment_type<allocator_type>::FlipStat(const cnf_type* cnf, variable_type variable) noexcept
{
  //  auto sign = assign[variable];
  //
  //  auto sat_clauses = cnf->ResolvingClauses(Lit(variable, sign));
  //  auto unsat_clauses = cnf->ResolvingClauses(Lit(variable, stl::Not(sign)));
  //
  //  auto stat = stl::Size(0);
  //
  //  for (auto index : sat_clauses)
  //    stat -= satisfied_counts[index] == 1 ? 1 : 0;
  //
  //  for (auto index : unsat_clauses)
  //    stat += satisfied_counts[index] == 0 ? 1 : 0;
  //
  //  return stat;

  auto stat = stl::Size(0);

  // clauses that may get unsat after flip
  const auto unsat = cnf->ResolvingClauses(Lit(variable, assign[variable]));

  // clauses that may get sat after flip
  const auto sat = cnf->ResolvingClauses(Lit(variable, stl::Not(assign[variable])));

  for (const auto index : unsat)
    if (satisfied_counts[index] == 1)
      --stat;

  for (const auto index : sat)
    if (satisfied_counts[index] == 0)
      ++stat;

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
