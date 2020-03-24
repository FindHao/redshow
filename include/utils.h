#ifndef REDSHOW_UTILS_H
#define REDSHOW_UTILS_H

#include <tuple>
#include <string>

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

// We will change the bits after this index to 0. F32:23, F64:52
const int VALID_FLOAT_DIGITS = 23;
const int VALID_DOUBLE_DIGITS = 52;

const int MIN_FLOAT_DIGITS = 20;
const int MIN_DOUBLE_DIGITS = 46;

const int LOW_FLOAT_DIGITS = 17;
const int LOW_DOUBLE_DIGITS = 40;

const int MID_FLOAT_DIGITS = 14;
const int MID_DOUBLE_DIGITS = 34;

const int HIGH_FLOAT_DIGITS = 11;
const int HIGH_DOUBLE_DIGITS = 28;

const int MAX_FLOAT_DIGITS = 8;
const int MAX_DOUBLE_DIGITS = 22;

#endif  // REDSHOW_UTILS_H
