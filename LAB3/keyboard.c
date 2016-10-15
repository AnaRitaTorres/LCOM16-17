#include "keyboard.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8042.h"
#include "i8254.h"
#include "timer.h"

static int hook_id_kbd;

int keyboard_subscribe_int(){
	hook_id_kbd = IRQ_KBD;
	if (sys_irqsetpolicy(IRQ_KBD, IRQ_REENABLE|IRQ_EXCLUSIVE, &hook_id_kbd) == OK)
			return IRQ_KBD;
	else
	{
		printf("Sys_irqserpolicy failed!\n");
		return -1;
	}
}

}
int keyboard_unsubscribe_int(){

	if( sys_irqrmpolicy(&hook_id_kbd) ==OK)
		return 0;
	else
	{
		printf("Sys_irqrmpolicy failed!\n");
		return -1;
	}
}
