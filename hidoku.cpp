#include <sls/cnf.hpp>
#include <stl/range.hpp>

using namespace stl;
using namespace sls;

struct hidoku_type
{
  vector_type<literal_type, 10'000> data;
  size_type w;
  size_type h;
  size_type n;

  size_type num_variables;
  size_type num_clauses;

  literal_type At(size_type x, size_type y) const { return *data.At(y * w + x); }

  literal_type Var(size_type x, size_type y, size_type i) { return Literal((y * w + x) * n + (i - 1)); }
  literal_type SVar(size_type x, size_type y, size_type i) { return Literal((w * h * n) + (y * w + x) * (n - 1) + (i - 1)); }

  void PostProcess()
  {
    num_variables = w * h * n;
    num_clauses = 0;

    for (auto x : Range(0, w)) {
      for (auto y : Range(0, w)) {
        if (At(x, y)) {
          num_clauses += 1;
          num_clauses += 1;
        } else {
          num_clauses += (n - 2) * 3 + 2;
          num_clauses += (n - 1);
        }
        num_variables += n - 1;
      }
    }
  }
};

literal_type
Not(literal_type literal)
{
  return literal ^ 1;
}

hidoku_type
Hidoku()
{
  hidoku_type hidoku;
  hidoku.w = 4;
  hidoku.h = 4;
  hidoku.n = 16;

  hidoku.data = Vector<literal_type, 10'000>();
  hidoku.data.Count(hidoku.w * hidoku.h);
  View(&hidoku.data).MemSet(0);

  *hidoku.data.At(0) = 1;
  *hidoku.data.At(3) = 5;
  *hidoku.data.At(5) = 7;
  *hidoku.data.At(11) = 14;
  *hidoku.data.At(14) = 16;

  hidoku.PostProcess();

  return hidoku;
}

int
main()
{
  auto hidoku = Hidoku();
  auto cnf = CnfExtended(hidoku.num_variables, hidoku.num_clauses);

//  for (auto x : Range(0, hidoku.w)) {
//    for (auto y : Range(0, hidoku.w)) {
//
//      if (hidoku.At(x, y)) {
//
//        cnf.Push(hidoku.Var(x, y, hidoku.At(x, y)));
//        cnf.Push();
//
//      } else {
//
//        cnf.Push(Not(hidoku.Var(x, y, 1)));
//        cnf.Push(hidoku.SVar(x, y, 1));
//        cnf.Push();
//
//        for (auto i : Range(1, hidoku.n)) {
//
//          cnf.Push(Not(hidoku.Var(x, y, i)));
//          cnf.Push(hidoku.SVar(x, y, i));
//          cnf.Push();
//
//          cnf.Push(Not(hidoku.SVar(x, y, i - 1)));
//          cnf.Push(hidoku.SVar(x, y, i));
//          cnf.Push();
//
//          cnf.Push(Not(hidoku.Var(x, y, i)));
//          cnf.Push(Not(hidoku.SVar(x, y, i - 1)));
//          cnf.Push();
//        }
//
//        cnf.Push(Not(hidoku.Var(x, y, hidoku.n)));
//        cnf.Push(Not(hidoku.SVar(x, y, hidoku.n - 1)));
//        cnf.Push();
//      }
//    }
//  }
//
//  for (auto x : Range(0, hidoku.w)) {
//    for (auto y : Range(0, hidoku.w)) {
//
//      if (hidoku.At(x, y)) {
//
//        if (hidoku.At(x, y) == hidoku.n)
//          continue;
//
//        size_type i = hidoku.At(x, y);
//        cnf.Push(Not(hidoku.Var(x, y, i)));
//        if (x - 1 > 0 && y - 1 > 0)
//          cnf.Push(hidoku.Var(x - 1, y - 1, i + 1));
//        if (x - 1 > 0)
//          cnf.Push(hidoku.Var(x - 1, y + 0, i + 1));
//        if (x - 1 > 0 && y + 1 < hidoku.h)
//          cnf.Push(hidoku.Var(x - 1, y + 1, i + 1));
//        if (y - 1 > 0)
//          cnf.Push(hidoku.Var(x + 0, y - 1, i + 1));
//        if (y + 1 < hidoku.h)
//          cnf.Push(hidoku.Var(x + 0, y + 1, i + 1));
//        if (x + 1 < hidoku.w && y - 1 > 0)
//          cnf.Push(hidoku.Var(x + 1, y - 1, i + 1));
//        if (x + 1 < hidoku.w)
//          cnf.Push(hidoku.Var(x + 1, y + 0, i + 1));
//        if (x + 1 < hidoku.w && y + 1 < hidoku.h)
//          cnf.Push(hidoku.Var(x + 1, y + 1, i + 1));
//        cnf.Push();
//
//      } else {
//
//        for (auto i : Range(1, hidoku.n)) {
//          cnf.Push(Not(hidoku.Var(x, y, i)));
//          if (x - 1 > 0 && y - 1 > 0)
//            cnf.Push(hidoku.Var(x - 1, y - 1, i + 1));
//          if (x - 1 > 0)
//            cnf.Push(hidoku.Var(x - 1, y + 0, i + 1));
//          if (x - 1 > 0 && y + 1 < hidoku.h)
//            cnf.Push(hidoku.Var(x - 1, y + 1, i + 1));
//          if (y - 1 > 0)
//            cnf.Push(hidoku.Var(x + 0, y - 1, i + 1));
//          if (y + 1 < hidoku.h)
//            cnf.Push(hidoku.Var(x + 0, y + 1, i + 1));
//          if (x + 1 < hidoku.w && y - 1 > 0)
//            cnf.Push(hidoku.Var(x + 1, y - 1, i + 1));
//          if (x + 1 < hidoku.w)
//            cnf.Push(hidoku.Var(x + 1, y + 0, i + 1));
//          if (x + 1 < hidoku.w && y + 1 < hidoku.h)
//            cnf.Push(hidoku.Var(x + 1, y + 1, i + 1));
//          cnf.Push();
//        }
//      }
//    }
//  }


//  std::cout << "p cnf " << cnf.num_variables << ' ' << cnf.num_clauses << '\n';
//
//  for (auto clause : cnf) {
//    for (auto lit : clause) {
//      auto sign = lit & 1;
//      auto var = (lit >> 1) + 1;
//      std::cout << (sign ? "-" : "") << var << ' ';
//    }
//    std::cout << "0\n";
//  }
}
