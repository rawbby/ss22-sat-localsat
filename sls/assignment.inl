#ifndef SLS_ASSIGNMENT_INL
#define SLS_ASSIGNMENT_INL

#include "assignment.hpp"

namespace sls {
using namespace stl;

//  __  __   _____   _____   _   _    ___    ____    ____
// |  \/  | | ____| |_   _| | | | |  / _ \  |  _ \  / ___|
// | |\/| | |  _|     | |   | |_| | | | | | | | | | \___ \
// | |  | | | |___    | |   |  _  | | |_| | | |_| |  ___) |
// |_|  |_| |_____|   |_|   |_| |_|  \___/  |____/  |____/

[[maybe_unused]] constexpr inline void
assignment_type::Flip(const cnf_type* cnf, variable_type variable) noexcept
{
  auto* sig = assign.At(variable);
  *sig = !(*sig);

  auto sign = *(assign.At(variable));
  auto pos_literal = Literal(variable, sign);
  auto neg_literal = Literal(variable, !sign);

  auto pos_clause_index_iter = Iterator(cnf->ResolvingClauses(pos_literal));
  while (pos_clause_index_iter.HasNext()) {
    auto pos_clause_index = *(pos_clause_index_iter.Next());
    *(satisfied_counts.At(pos_clause_index)) += 1;
  }

  auto neg_clause_index_iter = Iterator(cnf->ResolvingClauses(neg_literal));
  while (neg_clause_index_iter.HasNext()) {
    auto neg_clause_index = *(neg_clause_index_iter.Next());
    *(satisfied_counts.At(neg_clause_index)) -= 1;
  }
}

[[maybe_unused]] inline void
assignment_type::RandomFlip(const cnf_type* cnf, random_type random) noexcept
{
  variable_type variable = random.randInt(cnf->num_variables);
  auto* sig = assign.At(variable);
  *sig = !(*sig);

  auto sign = *(assign.At(variable));
  auto pos_literal = Literal(variable, sign);
  auto neg_literal = Literal(variable, !sign);

  auto pos_clause_index_iter = Iterator(cnf->ResolvingClauses(pos_literal));
  while (pos_clause_index_iter.HasNext()) {
    auto pos_clause_index = *(pos_clause_index_iter.Next());
    *(satisfied_counts.At(pos_clause_index)) += 1;
  }

  auto neg_clause_index_iter = Iterator(cnf->ResolvingClauses(neg_literal));
  while (neg_clause_index_iter.HasNext()) {
    auto neg_clause_index = *(neg_clause_index_iter.Next());
    *(satisfied_counts.At(neg_clause_index)) -= 1;
  }
}

[[maybe_unused]] constexpr inline void
assignment_type::BestFlip(const cnf_type* cnf) noexcept
{
  auto best_var = Variable(0);
  auto best_stat = FlipStat(cnf, best_var);

  const auto n_var = cnf->num_variables;
  for (auto var = Variable(1); var < n_var; ++var) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
    }
  }

  Flip(cnf, best_var);
}

[[maybe_unused]] constexpr inline void
assignment_type::RandomReset(const cnf_type* cnf, random_type* random) noexcept
{
  stl_foreach(&assign, [&](auto & sign){
    sign = random->randBool();
  });

  // auto assign_iter = Iterator(&assign);
  // while (assign_iter.HasNext()) {
  //   *(assign_iter.Next()) = random->randBool();
  // }
  UpdateStats(cnf);
}

[[maybe_unused]] constexpr inline void
assignment_type::UpdateStats(const cnf_type* cnf) noexcept
{
  View(&satisfied_counts).MemSet(0);

  auto assign_iter = Iterator(&assign);
  auto variable = Variable(0);
  while (assign_iter.HasNext()) {
    auto sign = *(assign_iter.Next());
    auto literal = Literal(variable, sign);

    auto clause_index_iter = Iterator(cnf->ResolvingClauses(literal));
    while (clause_index_iter.HasNext()) {
      auto clause_index = *(clause_index_iter.Next());
      *(satisfied_counts.At(clause_index)) += 1;
    }

    variable++;
  }
}

[[maybe_unused]] [[nodiscard]] constexpr inline float
assignment_type::Score() noexcept
{
  auto score = satisfied_counts.Count();

  stl_foreach(&satisfied_counts, [&](auto count) {
    if (count)
      --score;
  });

  return score;
}

[[maybe_unused]] [[nodiscard]] constexpr inline size_type
assignment_type::FlipStat(const cnf_type* cnf, variable_type variable) noexcept
{
  auto sign = *(assign.At(variable));
  auto sat_clauses = cnf->ResolvingClauses(Literal(variable, sign));
  auto unsat_clauses = cnf->ResolvingClauses(Literal(variable, !sign));

  auto stat = Size(0);

  stl_foreach(sat_clauses, [&](auto index) {
    if (*(satisfied_counts.At(index)) == 1)
      --stat;
  });

  stl_foreach(unsat_clauses, [&](auto index) {
    if (*(satisfied_counts.At(index)) == 0)
      ++stat;
  });

  return stat;
}

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] [[nodiscard]] constexpr inline assignment_type
Assignment(const cnf_type* cnf) noexcept
{
  assignment_type assignment;

  assignment.assign = Vector<i8_type, MAX_VARIABLES>();
  assignment.assign.Count(cnf->num_variables);
  View(&assignment.assign).MemSet(I32(0));

  assignment.satisfied_counts = Vector<size_type, MAX_CLAUSES>();
  assignment.satisfied_counts.Count(cnf->num_clauses);
  View(&assignment.satisfied_counts).MemSet(I32(0));

  assignment.UpdateStats(cnf);

  return assignment;
}

[[maybe_unused]] [[nodiscard]] inline assignment_type
Assignment(const cnf_type* cnf, random_type* random) noexcept
{
  assignment_type assignment;

  assignment.assign = Vector<i8_type, MAX_VARIABLES>();
  assignment.assign.Count(cnf->num_variables);
  View(&assignment.assign).MemSet(I32(0));

  assignment.satisfied_counts = Vector<size_type, MAX_CLAUSES>();
  assignment.satisfied_counts.Count(cnf->num_clauses);
  View(&assignment.satisfied_counts).MemSet(I32(0));

  assignment.RandomReset(cnf, random);

  return assignment;
}

//  ___   _____   _____   ____       _      _____    ___    ____
// |_ _| |_   _| | ____| |  _ \     / \    |_   _|  / _ \  |  _ \
//  | |    | |   |  _|   | |_) |   / _ \     | |   | | | | | |_) |
//  | |    | |   | |___  |  _ <   / ___ \    | |   | |_| | |  _ <
// |___|   |_|   |_____| |_| \_\ /_/   \_\   |_|    \___/  |_| \_\

[[maybe_unused]] [[nodiscard]] constexpr inline view_iterator_type<i8_type>
Iterator(assignment_type* assign) noexcept
{
  return Iterator(&(assign->assign));
}

}

#endif
