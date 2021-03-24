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
#include "stdint.h"

/**
 * This file is manipulated by ERIC
 */

typedef struct _cpuid_solution {
  solution_header h;
  uint64_t s[4]; // rax, rbx, rcx, rdx
} __attribute__((packed)) cpuid_solution;

cpuid_solution s __attribute__((section(".solution"))) = {
  // Solution header
  .h = {
    .size = sizeof(cpuid_solution), // Size of the solution
    .time = 0x250,                  // expected execution time in micro fbb
    .bar_bitmap = (uint32_t)-1,     // The expected BAR
  },
  // Solution : CPUID space xor
  .s = {
    0x000000006d3020dc, // rax
    0x00000000744ef43c, // rbc
    0x00000000139f8de4, // rcx
    0x00000000f64bb2b5  // rdx
  }
};
