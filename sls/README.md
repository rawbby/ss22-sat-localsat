# SLS

Author: Robert Andreas Fritsch\
Date: 15.06.2022

Header only library for stochastic local search.

## Options

**SLS_OPTION\_MAX\_VARIABLES**\
specifies the upper bound for container storing variable.\
_Note: By default this value is set to 384._

**SLS_OPTION\_MAX\_CLAUSES**\
Specifies the upper bound for container storing clauses.\
_Note: By default this value is set to 5 times SLS_MAX_VARIABLES._

**SLS_OPTION\_MAX\_CNF\_LITERALS**\
Specifies the upper bound for buffer storing all literals of a cnf.\
_Note: By default this value is set to 5 times SLS_MAX_CLAUSES._

**SLS_OPTION\_ALLOCATE\_HEAP**\
Specifies whether to use the heap for allocating container.\
This might be necessary if you increase SLS_OPTION_MAX_ options to avoid a stack overflow.

**SLS_OPTION\_NO\_FREE**\
Specifies whether to free the heap after allocating container on the heap.\
This might be usefully for benchmarks in competitions.
Not freeing is secure if only a small number of instance is solved as each instance allocates a deterministic amount of
memory (depending in SLS_OPTION_MAX_ options).\
_Note: Ignored if SLS_OPTION\_ALLOCATE\_HEAP is unset._
