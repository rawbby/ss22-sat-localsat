#include <sls/assignment.hpp>
#include <sls/cnf.hpp>
#include <sls/dimacs.hpp>
#include <sls/sls.hpp>

#include <iostream>

using namespace stl;
using namespace sls;

int
main(int argc, char** argv)
{
  Assert(argc > 1, "No Parameter passed!");
#ifdef WIN32
  FILE* f;
  Assert(!fopen_s(&f, argv[1], "r"), "Failed to open File!");
#else
  FILE* f = fopen(argv[1], "r");
  Assert(f, "Failed to open File!");
#endif

  cnf_type cnf;
  ParseDimacs(f, &cnf);
  cnf.PostProcess();

  auto assign = SLS(&cnf);

  std::cout << "p cnf " << cnf.num_variables << ' ' << cnf.num_clauses << '\n';
  std::cout << "s SATISFIABLE\n";

  {
    std::cout << "v ";
    auto var = Variable(0);
    for (auto sign : assign)
      std::cout << (sign ? "-" : "") << ++var << ' ';
    std::cout << "0\n";
  }

  for (auto clause : cnf) {
    for (auto lit : clause) {
      auto sign = lit & 1;
      auto var = (lit >> 1) + 1;
      std::cout << (sign ? "-" : "") << var << ' ';
    }
    std::cout << "0\n";
  }

  return assign.Score();
}
