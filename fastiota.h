#ifndef FAST_IOTA_H__
#define FAST_IOTA_H__
#include <stdint.h>
#include <stdlib.h>
#ifdef SINGLE_HEADER_FAST_IOTA
#define FASTIOTA_EXPORT static inline
#else
#define FASTIOTA_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
FASTIOTA_EXPORT uint32_t *fastiota32(uint32_t *start, size_t nelem, uint32_t sv);
FASTIOTA_EXPORT int32_t *fastiota32i(int32_t *start, size_t nelem, int32_t sv);
FASTIOTA_EXPORT uint64_t *fastiota64(uint64_t *start, size_t nelem, uint64_t sv);
FASTIOTA_EXPORT int64_t *fastiota64i(int64_t *start, size_t nelem, int64_t sv);
#ifdef __cplusplus
}
#endif

#ifdef SINGLE_HEADER_FAST_IOTA
#include <fastiota.c>
#endif

#ifdef __cplusplus
namespace fastiota {
template<typename IT, typename IT2>
IT *iota(IT *start, size_t nelem, IT2 firstv=IT(0)) {
    if(sizeof(IT) == 4) {
        return reinterpret_cast<IT *>(fastiota32(reinterpret_cast<uint32_t *>(start), nelem, firstv));
    }
    if(sizeof(IT) == 8) {
        return reinterpret_cast<IT *>(fastiota64(reinterpret_cast<uint64_t *>(start), nelem, firstv));
    }
    IT *ptr = start, *end = start + nelem;
    while(ptr + 8 <= end) {
        ptr[0] = firstv;
        ptr[1] = firstv + 1;
        ptr[2] = firstv + 2;
        ptr[3] = firstv + 3;
        ptr[4] = firstv + 4;
        ptr[5] = firstv + 5;
        ptr[6] = firstv + 6;
        ptr[7] = firstv + 7;
        ptr += 8;
        firstv += 8;
    }
    while(ptr < end) *ptr++ = firstv++;
    return start;
}
template<typename Iterator, typename Integer>
void fastiota(Iterator start, Iterator stop, Integer sv=0) {
    iota(&*start, std::distance(start, stop), sv);
}
}
#endif

#endif /* FAST_IOTA_H__ */
