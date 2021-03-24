/*
Copyright (C) 2021  Benoît Morgan

This file is part of abyme

abyme is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

abyme is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with abyme.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "env/challenge.h"
#include "stdio.h"

// CPUID  O - f and 80000000 - 8000008
static inline void cpuid(void) {
  uint64_t rax, rbx, rcx, rdx;
  uint32_t i, j;
  uint64_t xor[4];
  for (j = 0; j < 0x100; j++) {
    xor[0] = 0, xor[1] = 0, xor[2] = 0, xor[3] = 0;
    // 0 to f
    for (i = 0; i < 0x10; i++) {
      rax = i, rbx = 0x0, rcx = 0x0, rdx = 0x0;
      __asm__ __volatile__("cpuid" : "=a"(rax), "=b"(rbx),
          "=c"(rcx), "=d"(rdx) : "a"(rax), "b"(rbx), "c"(rcx), "d"(rdx));
      xor[0] ^= rax, xor[1] ^= rbx, xor[2] ^= rcx, xor[3] ^= rdx;
    }
    // 80000000 - 80000008
    for (i = 0x80000000; i < 0x9; i++) {
      rax = i, rbx = 0x0, rcx = 0x0, rdx = 0x0;
      __asm__ __volatile__("cpuid" : "=a"(rax), "=b"(rbx),
          "=c"(rcx), "=d"(rdx) : "a"(rax), "b"(rbx), "c"(rcx), "d"(rdx));
      xor[0] ^= rax, xor[1] ^= rbx, xor[2] ^= rcx, xor[3] ^= rdx;
    }
  }
  // MMIO DW Access is mandatory to write the solution
  for (i = 0; i < 4; i++) {
    systab->answer[2 * i] = (xor[i] >> 0x00) & 0xffffffff;
    systab->answer[2 * i + 1] = (xor[i] >> 0x20) & 0xffffffff;
  }
}

void challenge_start(void) {
  cpuid();
}
