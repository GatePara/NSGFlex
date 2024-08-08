#include <iostream>
#include <../include/efanna2e/platform.h>

int main() {
    #if defined(USE_SSE)
    std::cout << "SSE is supported." << std::endl;
    #endif

    #if defined(USE_AVX)
    std::cout << "AVX is supported." << std::endl;
    #endif

    #if defined(USE_AVX2)
    std::cout << "AVX2 is supported." << std::endl;
    #endif

    #if defined(USE_AVX512)
    std::cout << "AVX512 is supported." << std::endl;
    #endif

    #if defined(USE_NEON)
    std::cout << "NEON is supported." << std::endl;
    #endif

    #if defined(NO_SUPPORT_PLATFORM)
    std::cout << "No supported platform-specific optimizations available." << std::endl;
    #endif

    return 0;
}
