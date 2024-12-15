#ifndef PLATFORM_H
#define PLATFORM_H

#include <cstdint>
#include <cstddef>

// Define macros for operating systems
#define OS_WINDOWS 1
#define OS_MACOS   2
#define OS_LINUX   3
#define OS_UNIX    4
#define OS_POSIX   5
#define OS_UNKNOWN 0

// Detect operating system and set the OS macro
#if defined(_WIN32) || defined(_WIN64)
    #define OS OS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS OS_MACOS
#elif defined(__linux__)
    #define OS OS_LINUX
#elif defined(__unix__)
    #define OS OS_UNIX
#elif defined(_POSIX_VERSION)
    #define OS OS_POSIX
#else
    #define OS OS_UNKNOWN
#endif

// Define macros for architecture
#define ARCH_32 32
#define ARCH_64 64
#define ARCH_UNKNOWN 0

// Detect architecture and set the ARCH macro
#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)
    #define ARCH ARCH_64
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__)
    #define ARCH ARCH_32
#else
    #define ARCH ARCH_UNKNOWN
#endif

// Define type aliases based on architecture
#if ARCH == ARCH_64
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using isize = ssize_t;
using usize = size_t;

#elif ARCH == ARCH_32
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

using isize = ssize_t;
using usize = size_t;

#else
#error "Unsupported architecture detected. Cannot define type aliases."
#endif

#endif // PLATFORM_H
