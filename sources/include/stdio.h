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

#ifndef __STDIO_H__
#define __STDIO_H__

#include "env/challenge.h"
#include "systab.h"

static inline void _stdio_stop(void) {
  __asm__ __volatile__("cli");
  __asm__ __volatile__("hlt");
  while (1);
}

#define PRINTK(stop, msg, ...)                                       \
  do {                                                               \
    systab->printk("%s(%03d): ", __FUNCTION__, __LINE__);                    \
    systab->printk(msg);                                                     \
    systab->printk(__VA_ARGS__);                                             \
    if (stop == 1) {                                                 \
      _stdio_stop();                                                 \
    }                                                                \
  } while (0)

#define ERROR(...)  PRINTK(1, "<ERROR> ",  __VA_ARGS__)
#define ACTION(...) PRINTK(0, "<ACTION> ", __VA_ARGS__)
#define INFO(...)   PRINTK(0, "<INFO> ",   __VA_ARGS__)

#endif//__STDIO_H__
