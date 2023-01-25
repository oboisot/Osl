#ifndef SWAPENDIAN_H
#define SWAPENDIAN_H

#include <cstdint>     // For std::uint16_t, etc...
#include <cstring>     // For std::memcpy
#include <memory>      // For std::allocator
#include <type_traits> // For std::enable_if, std::is_same
#include <complex>

#if defined(bswap16) || defined(bswap32) || defined(bswap64)
#  error "unexpected define!" // freebsd may define these; probably just need to undefine them
#endif

#ifdef _WIN32     // Windows builtins swap functions
    #include <cstdlib>
    #define bswap16(x) _byteswap_ushort(x)
    #define bswap32(x) _byteswap_ulong(x)
    #define bswap64(x) _byteswap_uint64(x)
#elif __linux__  // Linux builtins swap functions
    #include <byteswap.h>
    #define bswap16(x) bswap_16(x)
    #define bswap32(x) bswap_32(x)
    #define bswap64(x) bswap_64(x)
#else
    static inline std::uint16_t bswap16(const std::uint16_t &x)
    {
        return (x << 8) | (x >> 8);
    }
    static inline std::uint32_t bswap32(const std::uint32_t &x)
    {
        std::uint32_t step16 = (x << 16) | (x >> 16);
        return ((step16 << 8) & 0xff00ff00) | ((step16 >> 8) & 0x00ff00ff);
    }
    static inline std::uint64_t bswap64(const std::uint64_t &x)
    {
        std::uint64_t step32 = (x << 32) | (x >>32);
        std::uint64_t step16 = ((step32 & 0x0000FFFF0000FFFFULL) << 16) | ((step32 & 0xFFFF0000FFFF0000ULL) >> 16);
        return ((step16 & 0x00FF00FF00FF00FFULL) << 8) | ((step16 & 0xFF00FF00FF00FF00ULL) >> 8);
    }
#endif


namespace Osl { // Osl namespace

namespace  Endian { // Osl::Endian namespace

// ====================================================
// ========== INPLACE SWAPPING OF ENDIANNESS ==========
// ====================================================
    // ***** Unsigned integers *****
inline void swapEndianInplace(std::uint16_t &x)
{
    x = bswap16(x);
}

inline void swapEndianInplace(std::uint32_t &x)
{
    x = bswap32(x);
}

inline void swapEndianInplace(std::uint64_t &x)
{
    x = bswap64(x);
}

    // ***** Signed integers *****
inline void swapEndianInplace(std::int16_t &x)
{
    x = static_cast<std::int16_t>( bswap16(static_cast<std::uint16_t>(x)) );
}

inline void swapEndianInplace(std::int32_t &x)
{
    x = static_cast<std::int32_t>( bswap32(static_cast<std::uint32_t>(x)) );
}

inline void swapEndianInplace(std::int64_t &x)
{
    x = static_cast<std::int64_t>( bswap64(static_cast<std::uint64_t>(x)) );
}

    // ***** Floating points *****
inline void swapEndianInplace(float &x)
{
    const std::size_t size = sizeof(std::uint32_t);
    static_assert(sizeof(float) == size, "Unexpected float format.");

    std::uint32_t x2;
    std::memcpy( &x2, &x, size );
    x2 = bswap32(x2);
    std::memcpy( &x, &x2, size );
    // std::uint32_t tmp = bswap32(*reinterpret_cast<std::uint32_t*>(&x)); // see : https://gist.github.com/jtbr/7a43e6281e6cca353b33ee501421860c
    // return *(reinterpret_cast<float*>(&tmp));
    // !! Aliasing violation with : *reinterpret_cast<std::uint32_t*>(&x) and *reinterpret_cast<float*>(&tmp)
    // !! => Better use memcpy (see : https://en.cppreference.com/w/cpp/string/byte/memcpy)
}

inline void swapEndianInplace(double &x)
{
    const std::size_t size = sizeof(std::uint64_t);
    static_assert(sizeof(double) == sizeof(std::uint64_t), "Unexpected double format.");

    std::uint64_t x2;
    std::memcpy( &x2, &x, size );
    x2 = bswap64(x2);
    std::memcpy( &x, &x2, size );
}

    // ***** Complex specialization *****
template <typename T>
inline typename std::enable_if <
        std::is_same<T, std::uint16_t>::value ||
        std::is_same<T, std::int16_t>::value  ||
        std::is_same<T, std::uint32_t>::value ||
        std::is_same<T, std::int32_t>::value  ||
        std::is_same<T, std::uint64_t>::value ||
        std::is_same<T, std::int64_t>::value  ||
        std::is_same<T, float>::value         ||
        std::is_same<T, double>::value,
        void>::type swapEndianInplace(std::complex<T> &z)
{
    T *pz = reinterpret_cast<T(&)[2]>(z); // Get a pointer to the first and second values of the complex array
    swapEndianInplace(pz[0]); // Real part
    swapEndianInplace(pz[1]); // Imaginary part
}

    // ***** Container with iterators specialization *****
template< typename T, template<typename, typename=std::allocator<T>> class Container >
inline typename std::enable_if <
        std::is_same<T, std::uint16_t>::value ||
        std::is_same<T, std::int16_t>::value  ||
        std::is_same<T, std::uint32_t>::value ||
        std::is_same<T, std::int32_t>::value  ||
        std::is_same<T, std::uint64_t>::value ||
        std::is_same<T, std::int64_t>::value  ||
        std::is_same<T, float>::value         ||
        std::is_same<T, double>::value,
        void>::type swapEndianInplace(Container<T> &container)
{
    for (auto it = container.begin() ; it != container.end() ; ++it)
    {
        swapEndianInplace(*it);
    }
}

    // ***** Container with iterators and complex type specialization *****
template< typename T, template<typename, typename=std::allocator<std::complex<T>>> class Container >
inline typename std::enable_if <
        std::is_same<T, std::uint16_t>::value ||
        std::is_same<T, std::int16_t>::value  ||
        std::is_same<T, std::uint32_t>::value ||
        std::is_same<T, std::int32_t>::value  ||
        std::is_same<T, std::uint64_t>::value ||
        std::is_same<T, std::int64_t>::value  ||
        std::is_same<T, float>::value         ||
        std::is_same<T, double>::value,
        void>::type swapEndianInplace(Container<std::complex<T>> &container)
{
    T *pcontainer;
    for (auto it = container.begin() ; it != container.end() ; ++it)
    {
        pcontainer = reinterpret_cast<T(&)[2]>(*it);
        swapEndianInplace(pcontainer[0]);
        swapEndianInplace(pcontainer[1]);
    }
}

    // ***** Array specialization *****
template< typename T, std::size_t N>
inline typename std::enable_if <
        std::is_same<T, std::uint16_t>::value ||
        std::is_same<T, std::int16_t>::value  ||
        std::is_same<T, std::uint32_t>::value ||
        std::is_same<T, std::int32_t>::value  ||
        std::is_same<T, std::uint64_t>::value ||
        std::is_same<T, std::int64_t>::value  ||
        std::is_same<T, float>::value         ||
        std::is_same<T, double>::value,
        void>::type swapEndianInplace( T(&array)[N] )
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        swapEndianInplace(array[i]);
    }
}


// =====================================================
// ============== REVERSION OF ENDIANNESS ==============
// =====================================================
    // ***** Unsigned integers *****
inline std::uint16_t swapEndian(const std::uint16_t &x)
{
    return bswap16(x);
}

inline std::uint32_t swapEndian(const std::uint32_t &x)
{
    return bswap32(x);
}

inline std::uint64_t swapEndian(const std::uint64_t &x)
{
    return bswap64(x);
}

    // ***** Signed integers *****
inline std::int16_t swapEndian(const std::int16_t &x)
{
    return static_cast<std::int16_t>( bswap16(static_cast<std::uint16_t>(x)) );
}

inline std::int32_t swapEndian(const std::int32_t &x)
{
    return static_cast<std::int32_t>( bswap32(static_cast<std::uint32_t>(x)) );
}

inline std::int64_t swapEndian(const std::int64_t &x)
{
    return static_cast<std::int64_t>( bswap64(static_cast<std::uint64_t>(x)) );
}

    // ***** Floating points *****
inline float swapEndian(const float &x)
{
    float x2 = x;
    swapEndianInplace(x2);
    return x2;
}

inline double swapEndian(const double &x)
{
    double x2 = x;
    swapEndianInplace(x2);
    return x2;
}

} // namespace Osl::Endian

} // namespace Osl

#endif // SWAP_ENDIAN_H
