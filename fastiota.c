#include "fastiota.h"
#ifndef FASTIOTA_C_H__
#define FASTIOTA_C_H__
#include <x86intrin.h>
#ifdef __cplusplus
extern "C" {
#endif

#if __AVX512F__
#define init_start(func, sv)   func(sv + 15, sv + 14, sv + 13, sv + 12, sv + 11, sv + 10, sv + 9, sv + 8, sv + 7, sv + 6, sv + 5, sv + 4, sv + 3, sv + 2, sv + 1, sv)
#define init_start64(func, sv) func(sv + 7, sv + 6, sv + 5, sv + 4, sv + 3, sv + 2, sv + 1, sv)
#elif __AVX2__
#define init_start(func, sv)   func(sv + 7, sv + 6, sv + 5, sv + 4, sv + 3, sv + 2, sv + 1, sv)
#define init_start64(func, sv) func(sv + 3, sv + 2, sv + 1, sv)
#elif __SSE2__
#define init_start(func, sv)   func(sv + 3, sv + 2, sv + 1, sv)
#define init_start64(func, sv) func(sv + 1, sv)
#endif


FASTIOTA_EXPORT uint32_t *fastiota32(uint32_t *start, size_t nelem, uint32_t sv) {
#if __AVX512F__
    uint32_t *const end = start + nelem, *const origstart = start;
    __m512i m = init_start(_mm512_set_epi32, sv);
    const __m512i inc = _mm512_set1_epi32(sizeof(m) / sizeof(uint32_t));
    _Pragma("gcc unroll 4")
    if((uint64_t)start % sizeof(m) == 0) {
        while(end - start >= sizeof(m) / sizeof(uint32_t)) {
            _mm512_store_si512((void *)start, m);
            m = _mm512_add_epi32(m, inc);
            start += sizeof(m) / sizeof(uint32_t);
        }
    } else {
        while(end - start >= sizeof(m) / sizeof(uint32_t)) {
            _mm512_storeu_si512((void *)start, m);
            m = _mm512_add_epi32(m, inc);
            start += sizeof(m) / sizeof(uint32_t);
        }
    }
    sv += (start - origstart);
#elif __AVX2__
    uint32_t *const end = start + nelem, *const origstart = start;
    __m256i m = init_start(_mm256_set_epi32, sv);
    const __m256i inc = _mm256_set1_epi32(sizeof(m) / sizeof(uint32_t));
    _Pragma("gcc unroll 4")
    if((uint64_t)start % sizeof(m) == 0) {
        while(end - start >= sizeof(m) / sizeof(uint32_t)) {
            _mm256_store_si256((__m256i *)start, m);
            m = _mm256_add_epi32(m, inc);
            start += sizeof(m) / sizeof(uint32_t);
        }
    } else {
        while(end - start >= sizeof(m) / sizeof(uint32_t)) {
            _mm256_storeu_si256((__m256i *)start, m);
            m = _mm256_add_epi32(m, inc);
            start += sizeof(m) / sizeof(uint32_t);
        }
    }
    sv += (start - origstart);
#elif __SSE2__
    uint32_t *const end = start + nelem, *const origstart = start;
    __m128i m = init_start(_mm_set_epi32, sv);
    const __m128i inc = _mm_set1_epi32(sizeof(m) / sizeof(uint32_t));
    _Pragma("gcc unroll 4")
    if((uint64_t)start % sizeof(m) == 0) {
        while(end - start >= sizeof(m) / sizeof(uint32_t)) {
            _mm_store_si128((__m128i *)start, m);
            m = _mm_add_epi32(m, inc);
            start += sizeof(m) / sizeof(uint32_t);
        }
    } else {
        while(end - start >= sizeof(m) / sizeof(uint32_t)) {
            _mm_storeu_si128((__m128i *)start, m);
            m = _mm_add_epi32(m, inc);
            start += sizeof(m) / sizeof(uint32_t);
        }
    }
    sv += (start - origstart);
#endif
    while(start < end) *start++ = sv++;
    return origstart;
}

FASTIOTA_EXPORT int32_t *fastiota32i(int32_t *start, size_t nelem, int32_t sv)
{
    return (int32_t *)fastiota32((uint32_t *)start, nelem, sv);
}
FASTIOTA_EXPORT uint64_t *fastiota64(uint64_t *start, size_t nelem, uint64_t sv) {
#if __AVX512F__
    uint64_t *const end = start + nelem, *const origstart = start;
    __m512i m = init_start64(_mm512_set_epi64, sv);
    const __m512i inc = _mm512_set1_epi64(sizeof(m) / sizeof(uint64_t));
    _Pragma("gcc unroll 4")
    if((uint64_t)start % sizeof(m) == 0) {
        while(end - start >= sizeof(m) / sizeof(uint64_t)) {
            _mm512_store_si512((void *)start, m);
            m = _mm512_add_epi64(m, inc);
            start += sizeof(m) / sizeof(uint64_t);
        }
    } else {
        while(end - start >= sizeof(m) / sizeof(uint64_t)) {
            _mm512_storeu_si512((void *)start, m);
            m = _mm512_add_epi64(m, inc);
            start += sizeof(m) / sizeof(uint64_t);
        }
    }
    sv += (start - origstart);
#elif __AVX2__
    uint64_t *const end = start + nelem, *const origstart = start;
    __m256i m = init_start64(_mm256_set_epi64x, sv);
    const __m256i inc = _mm256_set1_epi64x(sizeof(m) / sizeof(uint64_t));
    _Pragma("gcc unroll 4")
    if((uint64_t)start % sizeof(m) == 0) {
        while(end - start >= sizeof(m) / sizeof(uint64_t)) {
            _mm256_store_si256((__m256i *)start, m);
            m = _mm256_add_epi64(m, inc);
            start += sizeof(m) / sizeof(uint64_t);
        }
    } else {
        while(end - start >= sizeof(m) / sizeof(uint64_t)) {
            _mm256_storeu_si256((__m256i *)start, m);
            m = _mm256_add_epi64(m, inc);
            start += sizeof(m) / sizeof(uint64_t);
        }
    }
    sv += (start - origstart);
#elif __SSE2__
    uint64_t *const end = start + nelem, *const origstart = start;
    __m128i m = init_start64(_mm_set_epi64x, sv);
    const __m128i inc = _mm_set1_epi64x(sizeof(m) / sizeof(uint64_t));
    _Pragma("gcc unroll 4")
    if((uint64_t)start % sizeof(m) == 0) {
        while(end - start >= sizeof(m) / sizeof(uint64_t)) {
            _mm_store_si128((__m128i *)start, m);
            m = _mm_add_epi64(m, inc);
            start += sizeof(m) / sizeof(uint64_t);
        }
    } else {
        while(end - start >= sizeof(m) / sizeof(uint64_t)) {
            _mm_storeu_si128((__m128i *)start, m);
            m = _mm_add_epi64(m, inc);
            start += sizeof(m) / sizeof(uint64_t);
        }
    }
    sv += (start - origstart);
#endif
    while(start < end) *start++ = sv++;
    return origstart;
}

FASTIOTA_EXPORT int64_t *fastiota64i(int64_t *start, size_t nelem, int64_t sv)
{
    return (int64_t *)fastiota64((uint64_t *)start, nelem, sv);
}


#ifdef __cplusplus
}
#endif
#undef init_start
#undef init_start64

#endif /* FASTIOTA_C_H__ */
