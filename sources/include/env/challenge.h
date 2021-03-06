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
