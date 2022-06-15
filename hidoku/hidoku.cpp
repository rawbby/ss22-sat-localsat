//#define OPTION_PAIRWISE
//#define OPTION_SLS_SOLVE
//#define OPTION_VERBOSE

#ifdef OPTION_SLS_SOLVE
#ifndef OPTION_SLS_SMALL
// expect hidoku max 10x10
// good luck for bigger problems ...
// (might work, might fail)
#define OPTION_ALLOCATE_HEAP
#define OPTION_NO_FREE
#define OPTION_MAX_VARIABLES 19'900
#define OPTION_MAX_CLAUSES 39'402
#define OPTION_MAX_CNF_LITERALS 157'904
#endif
#include <sls/sls.hpp>
#endif

#include <sls/assignment.hpp>
#include <sls/cnf.hpp>
#include <stl/range.hpp>

using namespace stl;
using namespace sls;

struct hidoku_type
{
  vector_type<literal_type, 256> data;
  cnf_type cnf;
  size_type w;
  size_type h;
  size_type n;

  size_type si; // counter for generated variables

  size_type num_variables;
  size_type num_clauses;

  literal_type At(size_type x, size_type y) const { return *data.At(y * w + x); }

  // get a variable from the one hot pool
  literal_type Var(size_type x, size_type y, size_type i) { return Literal((x + y * w) * n + i); }

  // generate a new variable
  literal_type SVar() { return Literal((w * h * n) + si++); }

  // always invoke after data, w, h and n are initialized
  void PostProcess()
  {
    // calculate variables and clauses

    num_variables = w * h * n; // one hot encoding
    num_clauses = n;           // at least every number

    for (auto y : Range(0, h)) {
      for (auto x : Range(0, w)) {
        [[unlikely]] if (At(x, y))
        {
          num_clauses += n;                     // base constraint
          num_clauses += At(x, y) == n ? 0 : 1; // neighbor constraint
        }
        else
        {
          num_clauses += 1; // trivial at least once
#ifndef OPTION_PAIRWISE
          num_variables += n - 1;         // sequential at most once encoding
          num_clauses += (n - 2) * 3 + 2; // sequential at most once encoding
#else
          num_clauses += (n & 1 ? n : n - 1) * (n >> 1); // pairwise at most once encoding
#endif
          num_clauses += (n - 1); // neighbor constraint
        }
      }
    }

    cnf = CnfExtended(num_variables, num_clauses);

    // buffer for temporary / generated variables
    auto tmp_vars = Vector<literal_type, MAX_LITERALS>();

    // at least every number
    for (auto i : Range(0, n)) {
      for (auto y : Range(0, h)) {
        for (auto x : Range(0, w)) {
          Push(x, y, i);
        }
      }
      Push();
    }

    for (auto y : Range(0, h)) {
      for (auto x : Range(0, w)) {

        [[unlikely]] if (At(x, y))
        {

          // === base constrain ===

          auto m = At(x, y) - 1;

          for (auto i : Range(0, m)) {
            PushNot(x, y, i);
            Push();
          }

          Push(x, y, At(x, y) - 1);
          Push();

          for (auto i : Range(m + 1, n)) {
            PushNot(x, y, i);
            Push();
          }

          // === neighbor constraint ===

          [[unlikely]] if (At(x, y) == n)
            // skip highest number
            continue;

          size_type i = At(x, y) - 1;
          PushNot(x, y, i);
          Push(x - 1, y - 1, i + 1);
          Push(x - 1, y + 0, i + 1);
          Push(x - 1, y + 1, i + 1);
          Push(x + 0, y - 1, i + 1);
          Push(x + 0, y + 1, i + 1);
          Push(x + 1, y - 1, i + 1);
          Push(x + 1, y + 0, i + 1);
          Push(x + 1, y + 1, i + 1);
          Push();
        }
        else
        {

          // === trivial at least once constraint ===

          for (auto i : Range(0, n))
            Push(x, y, i);
          Push();

#ifdef OPTION_PAIRWISE

          // === pairwise encoder for at most once constraint ===

          for (auto i : Range(0, n)) {
            for (auto j : Range(i + 1, n)) {
              PushNot(x, y, i);
              PushNot(x, y, j);
              Push();
            }
          }
#else

          // === sequential encoder for at most once constraint ===

          // generate n-1 variables:
          tmp_vars.Count(Size(0));
          for ([[maybe_unused]] auto _ : Range(0, n - 1))
            tmp_vars.Push(SVar());

          // not X0 or s0
          PushNot(x, y, 0);
          Push(*tmp_vars.At(0));
          Push();

          // not Xn-1 or sn-2
          PushNot(x, y, n - 1);
          PushNot(*tmp_vars.At(n - 2));
          Push();

          // for (0 < i < n-1)
          for (auto i : Range(1, n - 1)) {

            //  not Xi   or     si
            PushNot(x, y, i);
            Push(*tmp_vars.At(i));
            Push();

            //  not si-1 or     si
            PushNot(*tmp_vars.At(i - 1));
            Push(*tmp_vars.At(i));
            Push();

            //  not Xi   or not si-1
            PushNot(x, y, i);
            PushNot(*tmp_vars.At(i - 1));
            Push();
          }
#endif

          // === neighbor constraint ===

          for (auto i : Range(0, n - 1)) {
            PushNot(x, y, i);
            Push(x - 1, y - 1, i + 1);
            Push(x - 1, y + 0, i + 1);
            Push(x - 1, y + 1, i + 1);
            Push(x + 0, y - 1, i + 1);
            Push(x + 0, y + 1, i + 1);
            Push(x + 1, y - 1, i + 1);
            Push(x + 1, y + 0, i + 1);
            Push(x + 1, y + 1, i + 1);
            Push();
          }
        }
      }
    }

    Assert(num_clauses == cnf.cnf.Count(), "Invalid cnf generation!");
    cnf.PostProcess();
  }

  void Push(size_type x, size_type y, size_type i)
  {
    Assert(i < n, "Invalid Variable Pushed!");
    [[likely]] if (x >= 0 && y >= 0 && x < w && y < h) Push(Var(x, y, i));
  }

  void PushNot(size_type x, size_type y, size_type i)
  {
    Assert(i < n, "Invalid Variable Pushed!");
    [[likely]] if (x >= 0 && y >= 0 && x < w || y < h) PushNot(Var(x, y, i));
  }

  void Push(size_type l)
  {
    Assert(l < num_variables, "Invalid Variable Pushed!");
    cnf.Push(l << 1);
  }

  void PushNot(size_type l)
  {
    Assert(l < num_variables, "Invalid Variable Pushed!");
    cnf.Push((l << 1) | 1);
  }

  void Push()
  {
    cnf.Push();
  }

  void InterpretAssignment(assignment_type* assign)
  {
    std::cout << "sol:" << w << ',' << h << ':';

    for (auto y : Range(0, h)) {
      for (auto x : Range(0, w)) {

        auto j = Size(0);

        for (auto i : Range(0, n)) {
          [[unlikely]] if (!*assign->assign.At(Var(x, y, i)))
          {
            j = i + 1;

            std::cout << j;

            if (x < w - 1)
              std::cout << ',';
            else
              std::cout << ';';

            break;
          }
        }
        [[unlikely]] if (j == n) continue;

        for (auto i : Range(j + 1, n))
          Assert(*assign->assign.At(Var(x, y, i)), "Field set multiple times!");
        Assert(j, "Field unset!");
      }
    }
    std::cout << std::endl;
  }
};

hidoku_type
Hidoku(char* arg)
{
  hidoku_type hidoku;

  auto c = I32(0);

  hidoku.w = 0;
  while (isdigit(arg[c]))
    hidoku.w = hidoku.w * 10 + (arg[c++] - '0');

  Assert(arg[c++] == ',', "Unexpected Token in Input String!");

  hidoku.h = 0;
  while (isdigit(arg[c]))
    hidoku.h = hidoku.h * 10 + (arg[c++] - '0');

  Assert(arg[c++] == ':', "Unexpected Token in Input String!");

  hidoku.n = hidoku.w * hidoku.h;
  hidoku.si = 0;

  Vector<literal_type, 256>(&hidoku.data);
  hidoku.data.Count(hidoku.w * hidoku.h);

  for (auto y : Range(0, hidoku.h)) {
    for (auto x : Range(0, hidoku.w)) {

      auto i = I32(0);
      while (isdigit(arg[c]))
        i = i * 10 + (arg[c++] - '0');

      Assert(i < hidoku.n, "Unexpected Input. Out of Bounds Hidoku Field!");
      *hidoku.data.At(y * hidoku.w + x) = i;

      [[likely]] if (x != hidoku.w - 1) Assert(arg[c++] == ',', "Unexpected Token in Input String!");
      else Assert(arg[c++] == ';', "Unexpected Token in Input String!");
    }
  }
  Assert(arg[c] == '\0', "Unexpected Token in Input String!");

  hidoku.PostProcess();
  return hidoku;
}

int
main(int argc, char** argv)
{
  Assert(argc > 1, "Expected an Input Parameter");
  auto hidoku = Hidoku(argv[1]);

#ifdef OPTION_SLS_SOLVE
  auto assign = SLS(&hidoku.cnf);
#endif

#ifdef OPTION_VERBOSE
  std::cout << "p cnf " << hidoku.cnf.num_variables << ' ' << hidoku.cnf.num_clauses << '\n';

#ifdef OPTION_SLS_SOLVE
  std::cout << "s SATISFIABLE\n";
  std::cout << "v ";
  {
    auto var = Variable(0);
    for (auto sign : assign)
      std::cout << (sign ? "-" : "") << ++var << ' ';
    std::cout << "0\n";
  }
#endif

  for (auto clause : hidoku.cnf) {
    for (auto lit : clause) {
      auto sign = lit & 1;
      auto var = (lit >> 1) + 1;
      std::cout << (sign ? "-" : "") << var << ' ';
    }
    std::cout << "0\n";
  }
#endif

#ifdef OPTION_SLS_SOLVE
  hidoku.InterpretAssignment(&assign);
#endif
}
