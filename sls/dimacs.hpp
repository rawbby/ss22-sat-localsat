#ifndef SLS_DIMACS_HPP
#define SLS_DIMACS_HPP

#include "sls.hpp"

namespace sls {
using namespace stl;

inline int32_t
ReadChar(FILE* f)
{
  int32_t c = getc(f);
  Assert(c != EOF, "Unexpected EOF. The DIMACS File is invalid!");
  return c;
}

void
ParseDimacs(FILE* f, cnf_type* cnf)
{
  char c;

  // skip comments
  while (ReadChar(f) == 'c')
    while (ReadChar(f) != '\n')
      ;

  Assert((c = ReadChar(f)) != 'p', "Invalid DIMACS. Expected Problem Line after Comments!");

  // read num_variables
  while (!isdigit(c = ReadChar(f)))
    ;
  int32_t num_variables = c - '0';
  while (isdigit(c = ReadChar(f))) {
    num_variables *= 10;
    num_variables += c - '0';
  }

  // read num_clauses
  while (!isdigit(c = ReadChar(f)))
    ;
  int32_t num_clauses = c - '0';
  while (isdigit(c = ReadChar(f))) {
    num_clauses *= 10;
    num_clauses += c - '0';
  }

  *cnf = CnfExtended(num_variables, num_clauses);

  int32_t literal;
  do {
    int32_t sig = 0;
    while (!isdigit(c = ReadChar(f)))
      sig = c;

    sig = (sig == '-') ? 0 : 1;

    literal = c - '0';
    while (isdigit(c = ReadChar(f))) {
      literal *= 10;
      literal += c - '0';
    }

    [[unlikely]] if (!literal) {
      cnf->Push();
      [[unlikely]] if (cnf->cnf.Count() >= num_clauses)
        break;

    } else {
      literal -= 1;
      literal <<= 1;
      literal = sig ? literal : literal | 1;

      cnf->Push(literal);
    }
  } while (true);

  // Do not block the solver by freeing resources :-P
  //fclose(f);
}

}

#endif
