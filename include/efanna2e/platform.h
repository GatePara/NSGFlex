#pragma once

#if defined(__GNUC__)
#define COMPILER_GCC
#elif defined(__clang__)
#define COMPILER_CLANG
#elif defined(_MSC_VER)
#define COMPILER_MSVC
#elif defined(__INTEL_COMPILER)
#define COMPILER_INTEL
#else
#define COMPILER_UNKNOWN
#endif

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

// #ifdef COMPILER_GCC
// #pragma message("Compiling with GCC")
// #elif defined(COMPILER_CLANG)
// #pragma message("Compiling with Clang")
// #elif defined(COMPILER_MSVC)
// #pragma message("Compiling with MSVC")
// #elif defined(COMPILER_INTEL)
// #pragma message("Compiling with Intel C++ Compiler")
// #else
// #pragma message("Unknown Compiler")
// #endif

#ifdef USE_AVX512
#pragma message("Using AVX-512 vectorization")
#elif defined(USE_AVX2)
#pragma message("Using AVX2 vectorization")
#elif defined(USE_AVX)
#pragma message("Using AVX vectorization")
#elif defined(USE_SSE2)
#pragma message("Using SSE2 vectorization")
#elif defined(USE_SSE)
#pragma message("Using SSE vectorization")
#elif defined(USE_NEON)
#pragma message("Using NEON vectorization")
#elif defined(NO_SUPPORT_PLATFORM)
#pragma message("No supported vectorization platform")
#endif