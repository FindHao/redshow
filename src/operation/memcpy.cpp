#include "operation/memcpy.h"

#include <string>

#include "common/hash.h"
#include "common/utils.h"

namespace redshow {

template<>
u64 compute_memcpy_redundancy<false>(u64 dst_start, u64 src_start, u64 len) {
  // compare every byte
  double same = 0;

  auto *dst_ptr = reinterpret_cast<unsigned char *>(dst_start);
  auto *src_ptr = reinterpret_cast<unsigned char *>(src_start);

// nested parallelism is fine
#ifdef OPENMP
  #pragma omp parallel for simd if (len > OMP_SEQ_LEN) reduction (+:same)
#endif
  for (size_t i = 0; i < len; ++i) {
    if (dst_ptr[i] == src_ptr[i]) {
      same += 1;
    }
  }

  return same;
}


template<>
u64 compute_memcpy_redundancy<true>(u64 dst_start, u64 src_start, u64 len) {
  // compare every byte
  double same = 0;

  auto *dst_ptr = reinterpret_cast<unsigned char *>(dst_start);
  auto *src_ptr = reinterpret_cast<unsigned char *>(src_start);

// nested parallelism is fine
#ifdef OPENMP
  #pragma omp parallel for simd if (len > OMP_SEQ_LEN) reduction (+:same)
#endif
  for (size_t i = 0; i < len; ++i) {
    if (dst_ptr[i] == src_ptr[i]) {
      same += 1;
    } else {
      dst_ptr[i] = src_ptr[i];
    }
  }

  return same;
}

}  // namespace redshow
