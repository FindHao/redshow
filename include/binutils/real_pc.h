#ifndef REDSHOW_BINUTILS_REAL_PC_H
#define REDSHOW_BINUTILS_REAL_PC_H

#include <queue>

#include "common/utils.h"
#include "common/vector.h"
#include "common/map.h"
#include "instruction.h"

namespace redshow {

struct RealPC {
  u32 cubin_id;
  u32 function_index;
  u64 pc_offset;

  RealPC() = default;

  RealPC(u32 cubin_id, u32 function_index, u64 pc_offset)
      : cubin_id(cubin_id), function_index(function_index), pc_offset(pc_offset) {}

  bool operator<(const RealPC &other) const {
    if (this->cubin_id == other.cubin_id) {
      if (this->function_index == other.function_index) {
        return this->pc_offset < other.pc_offset;
      }
      return this->function_index < other.function_index;
    }
    return this->cubin_id < other.cubin_id;
  }
};

struct RealPCPair {
  RealPC to_pc;
  RealPC from_pc;
  u64 value;
  AccessKind access_kind;
  u64 red_count;
  u64 access_count;

  RealPCPair() = default;

  RealPCPair(RealPC &to_pc, u64 value, AccessKind &access_kind, u64 red_count, u64 access_count)
      : to_pc(to_pc),
        value(value),
        access_kind(access_kind),
        red_count(red_count),
        access_count(access_count) {}

  RealPCPair(RealPC &to_pc, RealPC &from_pc, u64 value, AccessKind &access_kind, u64 red_count,
             u64 access_count)
      : to_pc(to_pc),
        from_pc(from_pc),
        value(value),
        access_kind(access_kind),
        red_count(red_count),
        access_count(access_count) {}
};

// {pc1 : {pc2 : {<value, AccessKind> : count}}}
typedef Map<u64, Map<u64, Map<std::pair<u64, AccessKind>, u64>>> PCPairs;

// {pc: access_count}
typedef Map<u64, u64> PCAccessCount;

struct CompareRealPCPair {
  bool operator()(RealPCPair const &r1, RealPCPair const &r2) {
    return r1.red_count > r2.red_count;
  }
};

typedef std::priority_queue<RealPCPair, Vector<RealPCPair>, CompareRealPCPair> TopRealPCPairs;


}  // namespace redshow

#endif  // REDSHOW_BINUTILS_REAL_PC_H