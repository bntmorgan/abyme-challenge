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
    .time = 0x200,                  // expected execution time in micro fbb
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
