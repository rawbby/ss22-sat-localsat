//#define OPTION_PAIRWISE
//#define OPTION_SLS_SOLVE
//#define OPTION_VERBOSE

#ifdef OPTION_SLS_SOLVE
#ifndef OPTION_SLS_SMALL
// expect hidoku max 10x10
// good luck for bigger problems ...
// (might work, might fail)
#define SLS_OPTION_ALLOCATE_HEAP
#define SLS_OPTION_NO_FREE
#define SLS_OPTION_MAX_VARIABLES 19'900
#define SLS_OPTION_MAX_CLAUSES 39'402
#define SLS_OPTION_MAX_CNF_LITERALS 157'904
#endif
#include <sls/sls.hpp>
#endif

#include <sls/assignment.hpp>
#include <sls/cnf.hpp>
#include <stl/range.hpp>

struct hidoku_type
{
  stl::static_vector_type<sls::literal_type, 256> data;
  stl::size_type w;
  stl::size_type h;
  stl::size_type n;

  stl::size_type si; // counter for generated variables

  stl::size_type num_variables;
  stl::size_type num_clauses;

  sls::literal_type At(stl::size_type x, stl::size_type y) const { return *data.At(y * w + x); }

  // get a variable from the one hot pool
  sls::literal_type Var(stl::size_type x, stl::size_type y, stl::size_type i) { return sls::Lit((x + y * w) * n + i); }

  // generate a new variable
  sls::literal_type SVar() { return sls::Lit((w * h * n) + si++); }

  // always invoke after data, w, h and n are initialized
  sls::cnf_type PostProcess()
  {
    // calculate variables and clauses

    num_variables = w * h * n; // one hot encoding
    num_clauses = n;           // at least every number

    for (auto y : stl::Range(0, h)) {
      for (auto x : stl::Range(0, w)) {
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

    sls::cnf_type cnf{ num_variables, num_clauses };

    // cnf_buffer for temporary / generated variables
    auto tmp_vars = stl::StaticVector<sls::literal_type, sls::SLS_MAX_LITERALS>();

    // at least every number
    for (auto i : stl::Range(0, n)) {
      for (auto y : stl::Range(0, h)) {
        for (auto x : stl::Range(0, w)) {
          Push(cnf, x, y, i);
        }
      }
      Push(cnf);
    }

    for (auto y : stl::Range(0, h)) {
      for (auto x : stl::Range(0, w)) {

        [[unlikely]] if (At(x, y))
        {

          // === base constrain ===

          auto m = At(x, y) - 1;

          for (auto i : stl::Range(0, m)) {
            PushNot(cnf, x, y, i);
            Push(cnf);
          }

          Push(cnf, x, y, At(x, y) - 1);
          Push(cnf);

          for (auto i : stl::Range(m + 1, n)) {
            PushNot(cnf, x, y, i);
            Push(cnf);
          }

          // === neighbor constraint ===

          [[unlikely]] if (At(x, y) == n)
            // skip highest number
            continue;

          stl::size_type i = At(x, y) - 1;
          PushNot(cnf, x, y, i);
          Push(cnf, x - 1, y - 1, i + 1);
          Push(cnf, x - 1, y + 0, i + 1);
          Push(cnf, x - 1, y + 1, i + 1);
          Push(cnf, x + 0, y - 1, i + 1);
          Push(cnf, x + 0, y + 1, i + 1);
          Push(cnf, x + 1, y - 1, i + 1);
          Push(cnf, x + 1, y + 0, i + 1);
          Push(cnf, x + 1, y + 1, i + 1);
          Push(cnf);
        }
        else
        {

          // === trivial at least once constraint ===

          for (auto i : stl::Range(0, n))
            Push(cnf, x, y, i);
          Push(cnf);

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
          tmp_vars.Count(stl::Size(0));
          for ([[maybe_unused]] auto _ : stl::Range(0, n - 1))
            tmp_vars.Push(SVar());

          // not X0 or s0
          PushNot(cnf, x, y, 0);
          Push(cnf, *tmp_vars.At(0));
          Push(cnf);

          // not Xn-1 or sn-2
          PushNot(cnf, x, y, n - 1);
          PushNot(cnf, *tmp_vars.At(n - 2));
          Push(cnf);

          // for (0 < i < n-1)
          for (auto i : stl::Range(1, n - 1)) {

            //  not Xi   or     si
            PushNot(cnf, x, y, i);
            Push(cnf, *tmp_vars.At(i));
            Push(cnf);

            //  not si-1 or     si
            PushNot(cnf, *tmp_vars.At(i - 1));
            Push(cnf, *tmp_vars.At(i));
            Push(cnf);

            //  not Xi   or not si-1
            PushNot(cnf, x, y, i);
            PushNot(cnf, *tmp_vars.At(i - 1));
            Push(cnf);
          }
#endif

          // === neighbor constraint ===

          for (auto i : stl::Range(0, n - 1)) {
            PushNot(cnf, x, y, i);
            Push(cnf, x - 1, y - 1, i + 1);
            Push(cnf, x - 1, y + 0, i + 1);
            Push(cnf, x - 1, y + 1, i + 1);
            Push(cnf, x + 0, y - 1, i + 1);
            Push(cnf, x + 0, y + 1, i + 1);
            Push(cnf, x + 1, y - 1, i + 1);
            Push(cnf, x + 1, y + 0, i + 1);
            Push(cnf, x + 1, y + 1, i + 1);
            Push(cnf);
          }
        }
      }
    }

    stl::Assert(num_clauses == cnf.cnf_clauses.Count() - 1, "Invalid cnf generation!");
    cnf.PostProcess();

    return cnf;
  }

  void Push(sls::cnf_type& cnf, stl::size_type x, stl::size_type y, stl::size_type i)
  {
    stl::Assert(i < n, "Invalid Variable Pushed!");
    [[likely]] if (x >= 0 && y >= 0 && x < w && y < h) Push(cnf, Var(x, y, i));
  }

  void PushNot(sls::cnf_type& cnf, stl::size_type x, stl::size_type y, stl::size_type i)
  {
    stl::Assert(i < n, "Invalid Variable Pushed!");
    [[likely]] if (x >= 0 && y >= 0 && x < w || y < h) PushNot(cnf, Var(x, y, i));
  }

  void Push(sls::cnf_type& cnf, stl::size_type l)
  {
    stl::Assert(l < num_variables, "Invalid Variable Pushed!");
    cnf.Push(l << 1);
  }

  void PushNot(sls::cnf_type& cnf, stl::size_type l)
  {
    stl::Assert(l < num_variables, "Invalid Variable Pushed!");
    cnf.Push((l << 1) | 1);
  }

  void Push(sls::cnf_type& cnf)
  {
    cnf.Push();
  }

  void InterpretAssignment(sls::assignment_type* assign)
  {
    std::cout << "sol:" << w << ',' << h << ':';

    for (auto y : stl::Range(0, h)) {
      for (auto x : stl::Range(0, w)) {

        auto j = stl::Size(0);

        for (auto i : stl::Range(0, n)) {
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

        for (auto i : stl::Range(j + 1, n))
          stl::Assert(*assign->assign.At(Var(x, y, i)), "Field set multiple times!");
        stl::Assert(j, "Field unset!");
      }
    }
    std::cout << std::endl;
  }
};

hidoku_type
Hidoku(char* arg)
{
  hidoku_type hidoku;

  auto c = stl::I32(0);

  hidoku.w = 0;
  while (isdigit(arg[c]))
    hidoku.w = hidoku.w * 10 + (arg[c++] - '0');

  stl::Assert(arg[c++] == ',', "Unexpected Token in Input String!");

  hidoku.h = 0;
  while (isdigit(arg[c]))
    hidoku.h = hidoku.h * 10 + (arg[c++] - '0');

  stl::Assert(arg[c++] == ':', "Unexpected Token in Input String!");

  hidoku.n = hidoku.w * hidoku.h;
  hidoku.si = 0;

  StaticVector<sls::literal_type, 256>(&hidoku.data);
  hidoku.data.Count(hidoku.w * hidoku.h);

  for (auto y : stl::Range(0, hidoku.h)) {
    for (auto x : stl::Range(0, hidoku.w)) {

      auto i = stl::I32(0);
      while (isdigit(arg[c]))
        i = i * 10 + (arg[c++] - '0');

      stl::Assert(i < hidoku.n, "Unexpected Input. Out of Bounds Hidoku Field!");
      *hidoku.data.At(y * hidoku.w + x) = i;

      [[likely]] if (x != hidoku.w - 1) stl::Assert(arg[c++] == ',', "Unexpected Token in Input String!");
      else stl::Assert(arg[c++] == ';', "Unexpected Token in Input String!");
    }
  }
  stl::Assert(arg[c] == '\0', "Unexpected Token in Input String!");

  return hidoku;
}

int
main(int argc, char** argv)
{
  stl::Assert(argc > 1, "Expected an Input Parameter");
  auto hidoku = Hidoku(argv[1]);
  auto cnf = hidoku.PostProcess();

#ifdef OPTION_SLS_SOLVE
  auto assign = SLS(&cnf);
#endif

#ifdef OPTION_VERBOSE
  std::cout << "p cnf " << cnf.num_variables << ' ' << cnf.num_clauses << '\n';

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

  for (auto clause : cnf.ClauseIterable()) {
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
