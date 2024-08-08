#pragma once

#ifndef NO_MANUAL_VECTORIZATION
#if (defined(__SSE__) || _M_IX86_FP > 0 || defined(_M_AMD64) || defined(_M_X64))
#define USE_SSE
#ifdef __SSE2__
#define USE_SSE2
#ifdef __AVX__
#define USE_AVX
#ifdef __AVX2__
#define USE_AVX2
#ifdef __AVX512F__
#define USE_AVX512
#endif
#endif
#endif
#endif
#endif

#if defined(__ARM_NEON)
#define USE_NEON
#endif

#endif

#if defined(USE_AVX) || defined(USE_SSE)
#include <x86intrin.h>
#include <cpuid.h>
#endif

#if defined(USE_NEON)
#include <arm_neon.h>
#endif

#if !defined(USE_SSE) && !defined(USE_AVX) && !defined(USE_NEON)
#define NO_SUPPORT_PLATFORM
#endif