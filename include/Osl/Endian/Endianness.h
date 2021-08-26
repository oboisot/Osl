#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#if __has_include(<bit>) // see : https://gcc.gnu.org/onlinedocs/libstdc++/manual/status.html
    #include <bit>
#endif

namespace Osl { // Osl namespace

namespace  Endian { // Osl::Endian namespace

#ifdef __cpp_lib_endian
    using Endianness = std::endian;
#else
    enum class Endianness  // see : https://en.cppreference.com/w/cpp/types/endian
    {
    #ifdef _WIN32  // see : https://github.com/microsoft/STL/blob/master/stl/inc/bit#L247
        little = 0,
        big    = 1,
        native = little
    #else         // see : https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/std/bit#L357
        little = __ORDER_LITTLE_ENDIAN__,
        big    = __ORDER_BIG_ENDIAN__,
        native = __BYTE_ORDER__
    #endif
    };
#endif

} // namespace Osl::Endian

} // namespace Osl

#endif // ENDIANNESS_H
