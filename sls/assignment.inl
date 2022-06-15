#ifndef SLS_ASSIGNMENT_INL
#define SLS_ASSIGNMENT_INL

#include "assignment.hpp"

#include <stl/range.hpp>

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
  auto& sign = *assign.At(variable);
  sign = !(sign);

  auto pos_literal = Literal(variable, sign);
  for (auto pos_clause_index : cnf->ResolvingClauses(pos_literal))
    *(satisfied_counts.At(pos_clause_index)) += 1;

  auto neg_literal = Literal(variable, !sign);
  for (auto neg_clause_index : cnf->ResolvingClauses(neg_literal))
    *(satisfied_counts.At(neg_clause_index)) -= 1;
}

[[maybe_unused]] inline void
assignment_type::RandomFlip(const cnf_type* cnf, random_type random) noexcept
{
  Flip(cnf, random.randInt(cnf->num_variables));
}

[[maybe_unused]] constexpr inline void
assignment_type::BestFlip(const cnf_type* cnf) noexcept
{
  // use loop_offset to start at new position
  // so less loops occur. this seems to be
  // very important! random seems to be more
  // efficient than loop_offset but tests are
  // required to prove.

  ++loop_offset;
  loop_offset = loop_offset < cnf->num_variables ? loop_offset : 0;

  auto best_var = Variable(0);
  auto best_stat = FlipStat(cnf, best_var);

  const auto n = loop_offset;
  const auto m = cnf->num_variables;

  for (auto var : Range(n, m)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
    }
  }
  for (auto var : Range(0, n)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
    }
  }

  Flip(cnf, best_var);
}

[[maybe_unused]] inline void
assignment_type::BestFlip(const cnf_type* cnf, random_type* random) noexcept
{
  // use random to start at new position
  // so less loops occur. this seems to
  // be very important!

  auto best_var = Variable(0);
  auto best_stat = FlipStat(cnf, best_var);

  const auto n = random->randInt(cnf->num_variables);
  const auto m = cnf->num_variables;

  for (auto var : Range(n, m)) {
    auto stat = FlipStat(cnf, var);
    if (stat > best_stat) {
      best_var = var;
      best_stat = stat;
    }
  }
  for (auto var : Range(0, n)) {
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
  for (auto& sign : assign)
    sign = random->randBool();

  UpdateStats(cnf);
}

[[maybe_unused]] constexpr inline void
assignment_type::UpdateStats(const cnf_type* cnf) noexcept
{
  View(&satisfied_counts).MemSet(0);

  auto variable = Variable(0);
  for (auto& sign : assign) {

    auto literal = Literal(variable, sign);

    for (auto clause_index : cnf->ResolvingClauses(literal))
      *satisfied_counts.At(clause_index) += 1;

    variable++;
  }
}

[[maybe_unused]] [[nodiscard]] constexpr inline float
assignment_type::Score() noexcept
{
  auto score = satisfied_counts.Count();
  for (auto count : satisfied_counts)
    score -= count ? 1 : 0;

  return score;
}

[[maybe_unused]] [[nodiscard]] constexpr inline size_type
assignment_type::FlipStat(const cnf_type* cnf, variable_type variable) noexcept
{
  auto sign = *assign.At(variable);
  auto sat_clauses = cnf->ResolvingClauses(Literal(variable, sign));
  auto unsat_clauses = cnf->ResolvingClauses(Literal(variable, !sign));

  auto stat = Size(0);

  for (auto index : sat_clauses)
    stat -= *satisfied_counts.At(index) == 1 ? 1 : 0;

  for (auto index : unsat_clauses)
    stat += *satisfied_counts.At(index) == 0 ? 1 : 0;

  return stat;
}

[[maybe_unused]] [[nodiscard]] constexpr inline i8_type*
assignment_type::begin() noexcept
{
  return assign.begin();
}

[[maybe_unused]] [[nodiscard]] constexpr inline i8_type*
assignment_type::end() noexcept
{
  return assign.end();
}

//   ____    ___    _   _   ____    _____   ____    _   _    ____   _____    ___    ____    ____
//  / ___|  / _ \  | \ | | / ___|  |_   _| |  _ \  | | | |  / ___| |_   _|  / _ \  |  _ \  / ___|
// | |     | | | | |  \| | \___ \    | |   | |_) | | | | | | |       | |   | | | | | |_) | \___ \
// | |___  | |_| | | |\  |  ___) |   | |   |  _ <  | |_| | | |___    | |   | |_| | |  _ <   ___) |
//  \____|  \___/  |_| \_| |____/    |_|   |_| \_\  \___/   \____|   |_|    \___/  |_| \_\ |____/

[[maybe_unused]] constexpr inline void
Assignment(assignment_type* assignment, const cnf_type* cnf) noexcept
{
  assignment->loop_offset = Size(0);

  assignment->assign = Vector<i8_type, MAX_VARIABLES>();
  assignment->assign.Count(cnf->num_variables);
  View(&assignment->assign).MemSet(I32(0));

  assignment->satisfied_counts = Vector<size_type, MAX_CLAUSES>();
  assignment->satisfied_counts.Count(cnf->num_clauses);
  View(&assignment->satisfied_counts).MemSet(I32(0));

  assignment->UpdateStats(cnf);
}

[[maybe_unused]] [[nodiscard]] constexpr inline assignment_type
Assignment(const cnf_type* cnf) noexcept
{
  assignment_type assignment;
  Assignment(&assignment, cnf);
  return assignment;
}

[[maybe_unused]] inline void
Assignment(assignment_type* assignment, const cnf_type* cnf, random_type* random) noexcept
{
  assignment->loop_offset = Size(0);

  assignment->assign = Vector<i8_type, MAX_VARIABLES>();
  assignment->assign.Count(cnf->num_variables);
  View(&assignment->assign).MemSet(I32(0));

  assignment->satisfied_counts = Vector<size_type, MAX_CLAUSES>();
  assignment->satisfied_counts.Count(cnf->num_clauses);
  View(&assignment->satisfied_counts).MemSet(I32(0));

  assignment->RandomReset(cnf, random);
}

[[maybe_unused]] [[nodiscard]] inline assignment_type
Assignment(const cnf_type* cnf, random_type* random) noexcept
{
  assignment_type assignment;
  Assignment(&assignment, cnf, random);
  return assignment;
}

}

#endif
