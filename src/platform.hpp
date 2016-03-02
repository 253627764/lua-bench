#pragma once

#include <cassert>

#ifdef _WIN32
#define LUA_BENCH_PLATFORM "Windows"
#elif defined(APPLE)
#define LUA_BENCH_PLATFORM "Windows"
#else
// Probably some kind of *Nix
#define LUA_BENCH_PLATFORM "*Nix"
#endif // Windows || Linux || Mac

#ifdef _MSC_VER
#define LUA_BENCH_VC 1
#define LUA_BENCH_COMPILER_TEXT "VC++"
#elif defined(__clang__)
#define LUA_BENCH_CLANG 1
#define LUA_BENCH_COMPILER_TEXT "clang++"
#elif defined(__MINGW32__)
#define LUA_BENCH_GCC 1
#define LUA_BENCH_MINGW 1
#define LUA_BENCH_COMPILER_TEXT "mingw g++"
#elif defined(__GNUC__)
#define LUA_BENCH_GCC 1
#define LUA_BENCH_COMPILER_TEXT "g++"
#elif defined(__EDG_VERSION__)
#define LUA_BENCH_EDG 1
#define LUA_BENCH_COMPILER_TEXT "edg"
#else
#error "Unknown compiler: specify"
#endif // Windows || Linux || Mac

#if INTPTR_MAX == INT64_MAX
#define LUA_BENCH_x64
#elif INTPTR_MAX == INT32_MAX
#define LUA_BENCH_x86
#else
#error Unknown pointer size or missing size macros!
#endif

#if defined __ARM__ || defined _M_ARM || defined _ARM || defined __aarch64__
#define LUA_BENCH_ARM
#endif

#ifndef NDEBUG
#define LUA_BENCH_DEBUG
#else
#define LUA_BENCH_RELEASE
#endif
