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
# Final execution report: total time = 1828182
#No   function                    calls      total time         percent            mean           stdev        relative
0     foo                            30         1766895           96.65           58896            3471            5.89
1     func_1                         50           61186            3.35            1223             425           34.75
2     func_2                         50           30529            1.67             610             211           34.59
```
