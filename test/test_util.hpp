#ifndef LOCALSAT_TEST_UTIL_HPP
#define LOCALSAT_TEST_UTIL_HPP
#define STL_OPTION_SANITIZE

#include <csignal>
#include <cstdlib>
#include <iostream>

#define TEST_ASSERT_EXIT_1(statement)                                                                                                          \
  auto _fail = [](int) {                                                                                                                       \
    std::cout << std::flush;                                                                                                                   \
    std::exit(1);                                                                                                                              \
  };                                                                                                                                           \
  auto _succ = []() {                                                                                                                          \
    std::cout << std::flush;                                                                                                                   \
    std::exit(0);                                                                                                                              \
  };                                                                                                                                           \
  std::atexit(_succ);                                                                                                                          \
  /* std::at_quick_exit(_succ); */                                                                                                             \
  signal(SIGABRT, _fail);                                                                                                                      \
  statement;                                                                                                                                   \
  std::abort()

#define TEST_STRINGIFY(x) #x
#define TEST_TO_STRING(x) TEST_STRINGIFY(x)
#define TEST_FAILURE_MESSAGE() "Test Failed! Line: " TEST_TO_STRING(__LINE__)

#endif
