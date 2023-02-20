#pragma once
#include <cstdint>
#include <type_traits>

// Constant-time comparison and selection of signed and unsigned integer values.
namespace subtle {

// Given two unsigned integers x, y of type operandT ( of bitwidth 8, 16, 32 or
// 64 ), this routine returns true ( if x == y ) or false ( in case x != y )
// testing equality of two values.
//
// We represent truth value using maximum number that can be represented using
// returnT i.e. all bits of returnT are set to one. While for false value, we
// set all bits of returnT to zero.
template<typename operandT, typename returnT>
static inline constexpr returnT
ct_eq(const operandT x, const operandT y)
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  const operandT a = x ^ y;
  const operandT b = a | (-a);
  const operandT c = b >> ((sizeof(operandT) * 8) - 1); // select only MSB
  const returnT d = -static_cast<returnT>(c ^ 1);       // prepare result

  return d;
}

// Given two unsigned integers x, y of type operandT ( of bitwidth 8, 16, 32 or
// 64 ), this routine returns true ( if x != y ) or false ( in case x == y )
// testing inequality of two values.
//
// We represent truth value using maximum number that can be represented using
// returnT i.e. all bits of returnT are set to one. While for false value, we
// set all bits of returnT to zero.
template<typename operandT, typename returnT>
static inline constexpr returnT
ct_ne(const operandT x, const operandT y)
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  const returnT z = ct_eq<operandT, returnT>(x, y);
  return ~z; // bit-inverted result of equality check
}

// Given a branch value br ( of type branchT ) holding either truth or false
// value and two unsigned integers x, y ( of bitwidth 8, 16, 32 or 64 ), this
// routine selects x if br is truth value or it returns y.
//
// Branch value br can have either of two values
//
// - truth value is represented using all bits of type branchT set to 1
// - false value is represented using all bits of type branchT set to 0
//
// If br takes any other value, this is an undefined behaviour !
template<typename branchT, typename operandT>
static inline constexpr operandT
ct_select(const branchT br, const operandT x, const operandT y)
  requires(std::is_unsigned_v<branchT> && std::is_unsigned_v<operandT>)
{
  const branchT z = br >> ((sizeof(branchT) * 8) - 1); // select MSB
  const operandT w = -static_cast<operandT>(z);        // bw(br) = bw(x) = bw(y)
  const operandT selected = (x & w) | (y & (~w));      // br ? x : y

  return selected;
}

// Given two unsigned integers x, y of type operandT ( of bitwidth 8, 16, 32 or
// 64 ), this routine returns truth value ( if x <= y ) or false value ( in case
// x > y ) based on result of lesser than equality test.
//
// We represent truth value using maximum number that can be represented using
// type returnT i.e. all bits of returnT are set to one. While for false value,
// we set all bits of returnT to zero.
//
// This implementation collects a lot of inspiration from
// https://github.com/dalek-cryptography/subtle/blob/bd282be01f1c2da8ab03922e03457102a76a0e05/src/lib.rs#L808-L841
//
// I also found
// https://cs.opensource.google/go/go/+/refs/tags/go1.20.1:src/crypto/subtle/constant_time.go;l=56-62
// to be pretty helpful.
template<typename operandT, typename returnT>
static inline constexpr returnT
ct_le(const operandT x, const operandT y)
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  const operandT gt_bits = x & ~y;
  operandT lt_bits = ~x & y;

  for (size_t pow = 1; pow < sizeof(operandT) * 8;) {
    lt_bits |= lt_bits >> pow;
    pow += pow;
  }

  operandT bit = gt_bits & ~lt_bits;

  for (size_t pow = 1; pow < sizeof(operandT) * 8;) {
    bit |= bit >> pow;
    pow += pow;
  }

  const returnT z = -static_cast<returnT>((bit & 1) ^ 1);
  return z;
}

// Given two unsigned integers x, y of type operandT ( of bitwidth 8, 16, 32 or
// 64 ), this routine returns truth value ( if x > y ) or false value ( in case
// x <= y ) based on result of greater than test.
//
// We represent truth value using maximum number that can be represented using
// type returnT i.e. all bits of returnT are set to one. While for false value,
// we set all bits of returnT to zero.
template<typename operandT, typename returnT>
static inline constexpr returnT
ct_gt(const operandT x, const operandT y)
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  const returnT z = ct_le<operandT, returnT>(x, y);
  return ~z; // bit-inverted result of <= test
}

}
