#include "env/challenge.h"
#include "stdio.h"

// CPUID  O - f
//        80000000 - 8000008

void challenge_start(void) {
  uint64_t rax, rbx, rcx, rdx;
  uint32_t i, j;
  uint64_t xor[4];
  for (j = 0; j < 0x100; j++) {
    // init
    xor[0] = 0, xor[1] = 0, xor[2] = 0, xor[3] = 0;
//    if (j > 50) {
//      i = 0;
//    }
    // 0 to f
    for (i = 0; i < 0x10; i++) {
      rax = i, rbx = 0x0, rcx = 0x0, rdx = 0x0;
      __asm__ __volatile__("cpuid" : "=a"(rax), "=b"(rbx), "=c"(rcx), "=d"(rdx) :
          "a"(rax), "b"(rbx), "c"(rcx), "d"(rdx));
      xor[0] ^= rax, xor[1] ^= rbx, xor[2] ^= rcx, xor[3] ^= rdx;
    }
    // 80000000 - 80000008
    for (i = 0x80000000; i < 0x9; i++) {
      rax = i, rbx = 0x0, rcx = 0x0, rdx = 0x0;
      __asm__ __volatile__("cpuid" : "=a"(rax), "=b"(rbx), "=c"(rcx), "=d"(rdx) :
          "a"(rax), "b"(rbx), "c"(rcx), "d"(rdx));
      xor[0] ^= rax, xor[1] ^= rbx, xor[2] ^= rcx, xor[3] ^= rdx;
    }
  }
  // MMIO DW Access is mandatory
  systab->answer[0x00] = (xor[0] >> 0x00) & 0xffffffff;
  systab->answer[0x01] = (xor[0] >> 0x20) & 0xffffffff;
  systab->answer[0x02] = (xor[1] >> 0x00) & 0xffffffff;
  systab->answer[0x03] = (xor[1] >> 0x20) & 0xffffffff;
  systab->answer[0x04] = (xor[2] >> 0x00) & 0xffffffff;
  systab->answer[0x05] = (xor[2] >> 0x20) & 0xffffffff;
  systab->answer[0x06] = (xor[3] >> 0x00) & 0xffffffff;
  systab->answer[0x07] = (xor[3] >> 0x20) & 0xffffffff;
}
