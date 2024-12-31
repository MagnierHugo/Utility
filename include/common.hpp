// Utility/common.hpp

#pragma once

#include <cstdint>
#include <memory>


#define tn typename
#define tmp template

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

tmp<tn T>
struct always_false : std::false_type {};