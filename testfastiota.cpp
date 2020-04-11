#include <cstdio>
#include <cassert>
#include <vector>
#include <numeric>
#include "fastiota.h"
int main() {
    int n = 400;
    std::vector<uint32_t> dat(n), datcmp(dat);
    uint32_t *ptr = dat.data();
    fastiota32(ptr, n, 13);
    std::iota(datcmp.begin(), datcmp.end(), 13u);
    assert(std::equal(dat.begin(), dat.end(), datcmp.begin()));
    for(uint32_t *s = ptr; s < ptr + n; ++s) fprintf(stderr, "%u,", *s);
    fputc('\n', stderr);
    std::vector<uint64_t> d64(n), dc64(n);
    fastiota::iota(d64.data(), d64.size(), 420);
    std::iota(dc64.data(), dc64.data() + n, uint64_t(420));
    for(auto s = d64.data(); s < d64.data() + n; ++s) fprintf(stderr, "%lu,", *s);
    assert(std::equal(d64.begin(), d64.end(), d64.begin()));
}
