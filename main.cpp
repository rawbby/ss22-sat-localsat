#include <sls/sls.hpp>
#include <sls/cnf.hpp>
#include <sls/assignment.hpp>
#include <sls/dimacs.hpp>

#include <iostream>

using namespace stl;
using namespace sls;

int
main(int argc, char** argv)
{
  FILE* f = fopen(argv[1], "r");
  Assert(f, "Failed to open File!");

  cnf_type cnf;
  ParseDimacs(f, &cnf);
  cnf.PostProcess();

  {
    std::cout << "cnf[";
    [[maybe_unused]] auto vector_stack_iter = Iterator(&cnf);
    while (vector_stack_iter.HasNext()) {
      [[maybe_unused]] auto view = vector_stack_iter.Next();
      [[maybe_unused]] auto view_iter = Iterator(view);
      std::cout << "[";
      while (view_iter.HasNext()) {
        std::cout << *view_iter.Next() << ',';
      }
      std::cout << "],";
    }
    std::cout << ']' << std::endl;
  }

  {
    std::cout << "vc[";
    [[maybe_unused]] auto vector_stack_iter = Iterator(&cnf.vc);
    while (vector_stack_iter.HasNext()) {
      [[maybe_unused]] auto view = vector_stack_iter.Next();
      [[maybe_unused]] auto view_iter = Iterator(view);
      std::cout << "[";
      while (view_iter.HasNext()) {
        std::cout << *view_iter.Next() << ',';
      }
      std::cout << "],";
    }
    std::cout << ']' << std::endl;
  }

  auto assign = SLS(&cnf);

  std::cout << "assign[";
  auto var = Variable(0);
  auto assign_iter = Iterator(&assign);
  while (assign_iter.HasNext()) {
    std::cout << I32(Literal(var, *assign_iter.Next())) << ',';
    var++;
  }
  std::cout << ']' << std::endl;

  return assign.Score();
}
