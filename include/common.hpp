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

using f32 = float;
using f64 = double;
using f128 = long double;

tmp<tn T>
struct always_false : std::false_type {};

tmp<tn T>
constexpr bool Is_Standard_Arithmetic_t = std::_Is_any_of_v<T, i8, u8, i16, u16, i32, u32, i64, u64, f32, f64, f128>;

tmp<tn T>
concept Standard_Arithmetic_t = Is_Standard_Arithmetic_t<T>;

tmp<tn T>
constexpr bool Is_Standard_Integer_t = std::_Is_any_of_v<T, i8, u8, i16, u16, i32, u32, i64, u64>;

tmp<tn T>
constexpr bool Is_Standard_Unsigned_Integer_t = std::_Is_any_of_v<T, u8, u16, u32, u64>;

tmp<tn T>
constexpr bool Is_Standard_Signed_Arithmetic_t = (Is_Standard_Arithmetic_t<T> && !Is_Standard_Unsigned_Integer_t<T>);

tmp<std::size_t N, std::size_t Q>
constexpr bool Is_Equal = N == Q;

tmp<std::size_t N, std::size_t Q>
concept Equal = Is_Equal<N, Q>;

struct discarder {
    tmp<tn T> constexpr inline void operator=(const T&) const noexcept {}
};

constexpr inline discarder _{};