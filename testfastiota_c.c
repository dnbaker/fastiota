#include <stdio.h>
#include "fastiota.h"
int main() {
    int n = 400;
    uint32_t *ptr = malloc(n * sizeof(uint32_t));
    fastiota32(ptr, n, 13);
    for(uint32_t *s = ptr; s < ptr + n; ++s) fprintf(stderr, "%u,", *s);
    fputc('\n', stderr);
    free(ptr);
}
