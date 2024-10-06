#include "drivers/cpu/detectCPU.h"
#include "console/console.h"
#include "console/print.h"

#define ECX_SSE3                        (1 << 0)
#define ECX_PCLMULQDQ                   (1 << 1)
#define ECX_DTES64                      (1 << 2)
#define ECX_MONITOR                     (1 << 3)
#define ECX_DS_CPL                      (1 << 4)
#define ECX_VMX                         (1 << 5)
#define ECX_SMX                         (1 << 6)
#define ECX_EST                         (1 << 7)
#define ECX_TM2                         (1 << 8)
#define ECX_SSSE3                       (1 << 9)
#define ECX_CNXT_ID                     (1 << 10)
#define ECX_FMA                         (1 << 12)
#define ECX_CX16                        (1 << 13)
#define ECX_XTPR                        (1 << 14)
#define ECX_PDCM                        (1 << 15)
#define ECX_PCID                        (1 << 17)
#define ECX_DCA                         (1 << 18)
#define ECX_SSE41                       (1 << 19)
#define ECX_SSE42                       (1 << 20)
#define ECX_X2APIC                      (1 << 21)
#define ECX_MOVBE                       (1 << 22)
#define ECX_POPCNT                      (1 << 23)
#define ECX_TSC                         (1 << 24)
#define ECX_AESNI                       (1 << 25)
#define ECX_XSAVE                       (1 << 26)
#define ECX_OSXSAVE                     (1 << 27)
#define ECX_AVX                         (1 << 28)
#define ECX_F16C                        (1 << 29)
#define ECX_RDRAND                      (1 << 30)

#define EDX_FPU                         (1 << 0)
#define EDX_VME                         (1 << 1)
#define EDX_DE                          (1 << 2)
#define EDX_PSE                         (1 << 3)
#define EDX_TSC                         (1 << 4)
#define EDX_MSR                         (1 << 5)
#define EDX_PAE                         (1 << 6)
#define EDX_MCE                         (1 << 7)
#define EDX_CX8                         (1 << 8)
#define EDX_APIC                        (1 << 9)
#define EDX_SEP                         (1 << 11)
#define EDX_MTRR                        (1 << 12)
#define EDX_PGE                         (1 << 13)
#define EDX_MCA                         (1 << 14)
#define EDX_CMOV                        (1 << 15)
#define EDX_PAT                         (1 << 16)
#define EDX_PSE36                       (1 << 17)
#define EDX_PSN                         (1 << 18)
#define EDX_CLFLUSH                     (1 << 19)
#define EDX_DS                          (1 << 21)
#define EDX_ACPI                        (1 << 22)
#define EDX_MMX                         (1 << 23)
#define EDX_FXSR                        (1 << 24)
#define EDX_SSE                         (1 << 25)
#define EDX_SSE2                        (1 << 26)
#define EDX_SS                          (1 << 27)
#define EDX_HTT                         (1 << 28)
#define EDX_TM                          (1 << 29)
#define EDX_PBE                         (1 << 31)

#define EDX_SYSCALL                     (1 << 11)
#define EDX_XD                          (1 << 20)
#define EDX_1GB_PAGE                    (1 << 26)
#define EDX_RDTSCP                      (1 << 27)
#define EDX_64_BIT                      (1 << 29)

static inline void cpuid(u32 reg, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx)
{
    __asm__ volatile("cpuid"
        : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
        : "0" (reg));
}

void CpuName() {
    char name[48];
    cpuid(0x80000002, (u32 *)(name +  0), (u32 *)(name +  4), (u32 *)(name +  8), (u32 *)(name + 12));
    cpuid(0x80000003, (u32 *)(name + 16), (u32 *)(name + 20), (u32 *)(name + 24), (u32 *)(name + 28));
    cpuid(0x80000004, (u32 *)(name + 32), (u32 *)(name + 36), (u32 *)(name + 40), (u32 *)(name + 44));

    char *p = name;
    while (*p == ' ')
    {
        ++p;
    }
    print_str(p);
}

