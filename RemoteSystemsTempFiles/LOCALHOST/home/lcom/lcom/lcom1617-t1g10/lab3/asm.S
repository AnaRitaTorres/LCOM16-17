#include "keyboard.h"

.global _kbd_scan_asm


.data

HAS_2_BYTE:
.byte 0;



.text
_handler_asm:
	xor %eax, %eax
	inb $OUT_BUF,%al
	cmp $TWO_BYTE_SCANCODE,%al
	je _end
	cmp $HAS_2_BYTE,1
	je _j1

_j1:
	shr $TWO_BYTE_SCANCODE,8 	//shift lógico de 8
	or %al,$TWO_BYTE_SCANCODE   //or lógico entre two_byte_scancode e o scancode
	mov $HAS_2_BYTE,0
	and %al,BREAK_CODE_BIT
	cmp %al,ESC

_end:
	mov $HAS_2_BYTE,1
	mov $0, %eax
	ret

