#include "i8042.h"

.global _kbd_scan_asm

.text
_kbd_scan_asm:
	xor %eax, %eax
	inb $OUT_BUF,%al
	ret


