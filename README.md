# Instrumentpp

A C++ library to measure function performance in C++.

# How to

If you have a CMake project, clone this code and put it in a folder like `lib/instrumentpp`

then in your `CMakeLists.txt` add it like:

```cmake
add_library(lib/instrumentpp)
```

Link your code against it and activate the instrumentation:

```cmake
target_link_libraries(<your_target> PRIVATE instrumentpp)
target_compile_definitions(<your_target> PRIVATE INSTRUMENTPP_ACTIVE)
```

In the `main` function of your code add the header and these 2 macros:

```c++
#include "instrument.h"

int main(void) {
  INSTRUMENTPP_CONSTRUCT;

  // your program

  INSTRUMENTPP_DESTROY;
}
```

Then instrument the functions you desire to profile:

```c++
int foo(void) {
  INSTRUMENTPP_START

  // your code
}
```

and compile your code with the `INSTRUMENTPP_ACTIVE` compilation flag:

```shell
gcc ... -DINSTRUMENTPP_ACTIVE
```

or with `cmake` in your project:

```shell
cmake -B build cmake -DINSTRUMENTPP_ACTIVE=On
```

After running your code, if it reaches the place where `INSTRUMENT_DESTROY` is, you should see in `stdout` something like:

```shell
...
# Final execution report: total time = 1093651
#     function                    calls      total time         percent            mean             min             max           stdev        relative
0     func_1                         30         1056893           96.64        35229.77           34321           38500          933.26            2.65
1     func_2                         50           36675            3.35          733.50             607            2619          271.05           36.95
2     func_3                         50           18522            1.69          370.44             303            1312          136.47           36.84
```
