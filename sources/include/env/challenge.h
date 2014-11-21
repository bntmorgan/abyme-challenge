#ifndef __CHALLENGE_H__
#define __CHALLENGE_H__

#include <stdint.h>

typedef struct _challenge_system_table {
  void (*printk) (char *format, ...);
  uint32_t *answer;
} challenge_system_table;

/**
 * These values are little endian and must be converted on big endian systems
 * The solution written in bar0 is following this header in memory
 */
typedef struct _solution_header {
  uint32_t size; // Total header + solution size
  uint32_t time; // Expected execution time in micro seconds
  uint32_t bar_bitmap; // Bar bitmap
} __attribute__((packed)) solution_header;

#endif//__CHALLENGE_H__
