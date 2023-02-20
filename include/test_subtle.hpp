#pragma once
#include "subtle.hpp"
#include <cassert>
#include <random>

// Test cases for ensuring functional correctness of constant-time comparison
// and selection operations
namespace subtle_test {

// Test functional correctness of constant-time equality operation over unsigned
// integer types, checking result against native comparison operator ( i.e. == )
template<typename operandT,
         typename returnT,
         const size_t iterations = (1ul << 16)>
void
test_ct_eq()
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  constexpr returnT truthv = -static_cast<returnT>(1);
  constexpr returnT falsev = 0;

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<operandT> dis;

  for (size_t i = 0; i < iterations; i++) {
    const operandT x = dis(gen);
    const operandT y = dis(gen);

    const returnT z = subtle::ct_eq<operandT, returnT>(x, y);
    assert(z == (x == y ? truthv : falsev));
  }
}

// Test functional correctness of constant-time inequality operation over
// unsigned integer types, checking result against native comparison operator
template<typename operandT,
         typename returnT,
         const size_t iterations = (1ul << 16)>
void
test_ct_ne()
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  constexpr returnT truthv = -static_cast<returnT>(1);
  constexpr returnT falsev = 0;

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<operandT> dis;

  for (size_t i = 0; i < iterations; i++) {
    const operandT x = dis(gen);
    const operandT y = dis(gen);

    const returnT z = subtle::ct_ne<operandT, returnT>(x, y);
    assert(z == (x != y ? truthv : falsev));
  }
}

// Test functional correctness of constant-time lesser than equality operation
// over unsigned integer types, checking result against native comparison op.
template<typename operandT,
         typename returnT,
         const size_t iterations = (1ul << 16)>
void
test_ct_le()
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  constexpr returnT truthv = -static_cast<returnT>(1);
  constexpr returnT falsev = 0;

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<operandT> dis;

  for (size_t i = 0; i < iterations; i++) {
    const operandT x = dis(gen);
    const operandT y = dis(gen);

    const returnT z = subtle::ct_le<operandT, returnT>(x, y);
    assert(z == (x <= y ? truthv : falsev));
  }
}

// Test functional correctness of constant-time greater than operation over
// unsigned integer types, checking result against native comparison operator.
template<typename operandT,
         typename returnT,
         const size_t iterations = (1ul << 16)>
void
test_ct_gt()
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  constexpr returnT truthv = -static_cast<returnT>(1);
  constexpr returnT falsev = 0;

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<operandT> dis;

  for (size_t i = 0; i < iterations; i++) {
    const operandT x = dis(gen);
    const operandT y = dis(gen);

    const returnT z = subtle::ct_gt<operandT, returnT>(x, y);
    assert(z == (x > y ? truthv : falsev));
  }
}

// Test functional correctness of constant-time greater than equality operation
// over unsigned integer types, checking result against native comparison op.
template<typename operandT,
         typename returnT,
         const size_t iterations = (1ul << 16)>
void
test_ct_ge()
  requires(std::is_unsigned_v<operandT> && std::is_unsigned_v<returnT>)
{
  constexpr returnT truthv = -static_cast<returnT>(1);
  constexpr returnT falsev = 0;

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<operandT> dis;

  for (size_t i = 0; i < iterations; i++) {
    const operandT x = dis(gen);
    const operandT y = dis(gen);

    const returnT z = subtle::ct_ge<operandT, returnT>(x, y);
    assert(z == (x >= y ? truthv : falsev));
  }
}

}
