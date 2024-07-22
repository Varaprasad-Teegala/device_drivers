#include <stdio.h>

int main() {
    printf("Compiler Information:\n");
#if defined(__GNUC__)
    printf("GCC version: <%d>.<%d>.<%d>\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

#if defined(__STDC__)
    printf("Standard C\n");
#endif

#if defined(__STDC_VERSION__)
    printf("C version: %ld\n", __STDC_VERSION__);
#endif

    printf("\nSystem Information:\n");
#if defined(__linux__)
    printf("Running on Linux\n");
#endif

#if defined(__unix__)
    printf("Running on a Unix-like system\n");
#elif defined(__APPLE__) && defined(__MACH__)
    printf("Running on macOS\n");
#endif

    printf("\nArchitecture Information:\n");
#if defined(__x86_64__)
    printf("Architecture: x86_64\n");
#elif defined(__i386__)
    printf("Architecture: x86\n");
#elif defined(__arm__)
    printf("Architecture: ARM\n");
#elif defined(__aarch64__)
    printf("Architecture: ARM64\n");
#endif

    printf("\nCode Location Information:\n");
    printf("This is file <%s>, line <%d>, in function <%s>\n", __FILE__, __LINE__, __FUNCTION__);

    return 0;
}

