### fastiota

For generating fast ranges of integers using SIMD types. (My typical use case is for using sorting a set of values by index rather than moving the values).

Example in C:

```c
#define SINGLE_HEADER_FAST_IOTA
#include <stdio.h>
#include "fastiota.h"

int main(int argc, char **argv) {
    uint64_t *ptr = malloc(100 * sizeof(uint64_t));
    uint32_t *ptr32 = malloc(100 * sizeof(uint32_t));
    size_t nelem = 100;
    fastiota64(ptr, nelem, 0);
    for(uint64_t *s = ptr; s < ptr + nelem; ++s)
        fprintf(stderr, "%lu,", (long unsigned)*s);
    fputs('\n', stderr);
    fastiota32(ptr, nelem, 0);
    for(uint32_t *s = ptr; s < ptr + nelem; ++s)
        fprintf(stderr, "%u,", *s);
    fputs('\n', stderr);
    free(ptr);
    free(ptr32);
    return 0;
}

```

Compile with `gcc -O3 <-msse2 for SSE2, -mavx2 for AVX2, -mavx512f for AVX512F> -o fastiotatest`.

In C++, it places a type-generic version which uses optimized c functions for operands of 32 or 64 bits,
has a default starting count of 0, and which falls back to an unrolled loop otherwise.

```c++
#include <cstdio>
#define SINGLE_HEADER_FAST_IOTA
#include "fastiota.h"
#include <vector>
int main() {
    std::vector<uint64_t> v64(100);
    std::vector<uint32_t> v32(100);
    fastiota::iota(v64.data(), v64.size(), 13);
    fastiota::iota(v32.data(), v32.size(), 137);
    for(const auto v: v64) std::fprintf(stderr, "%lu,", (long unsigned)v);
    std::fputc('\n', stderr);
    for(const auto v: v32) std::fprintf(stderr, "%u,", v);
    std::fputc('\n', stderr);

}
```
