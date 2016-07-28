.global systab
.extern challenge_start
.extern solution

# Challenge header
systab:
  .byte 0x00
  .byte 0x00
  .byte 0x00
  .byte 0x00
  .byte 0x00
  .byte 0x00
  .byte 0x00
  .byte 0x00

_start:
  cli
  push %rbp
  mov %rsp, %rbp
  callq challenge_start
  pop %rbp
  sti
  retq
