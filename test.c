#include <stdio.h>
#include "challenge.h"
#include "systab.h"

#include "stdint.h"

static uint16_t tsc_freq_MHz;
static uint8_t tsc_divider;
uint32_t s[0x400];
challenge_system_table *systab;

extern void challenge_start(void);

#define MSR_ADDRESS_MSR_PLATFORM_INFO               0x0ce
#define MSR_ADDRESS_IA32_VMX_MISC                   0x485

uint64_t cpu_read_tsc(void) {
  uint32_t tscl, tsch;
  __asm__ __volatile__("rdtsc" : "=d"(tsch), "=a"(tscl));  
  return ((uint64_t)tsch) << 32 | tscl;
}

uint64_t msr_read(uint64_t msr_address) {
  uint32_t eax, edx;
  __asm__ __volatile__("rdmsr" : "=a" (eax), "=d" (edx) : "c" (msr_address));
  return (((uint64_t) edx) << 32) | ((uint64_t) eax);
}

void msr_write(uint64_t msr_address, uint64_t msr_value) {
  __asm__ __volatile__("wrmsr" :
      : "a" (msr_value & 0xffffffff), "d" ((msr_value >> 32) & 0xffffffff), "c" (msr_address));
}

uint64_t env_tsc_to_micro(uint64_t t) {
  return (t << tsc_divider) / tsc_freq_MHz;
}

int main(int argc, char **argv) {
  uint64_t micros, a, b;
  // Init tsc
  tsc_freq_MHz = ((msr_read(MSR_ADDRESS_MSR_PLATFORM_INFO) >> 8) & 0xff) * 100;
  tsc_divider = msr_read(MSR_ADDRESS_IA32_VMX_MISC) & 0x7;
  // Systab
  // systab->printk = &printf;
  systab->answer = &s[0];
  // Challenge
  printf("Copy and execute challenge !\n");
  // Execution
  a = cpu_read_tsc();
  challenge_start();
  b = cpu_read_tsc();
  // Compute time in microseconds
  micros = env_tsc_to_micro(b - a);
  printf("Challenge execution time : 0x%016lx microseconds\n", micros);
  return 0;
}
