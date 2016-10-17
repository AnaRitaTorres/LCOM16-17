#include "test3.h"
#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include <minix/syslib.h>
#include <minix/drivers.h>


int kbd_test_scan(unsigned short ass) {
	int ipc_status;
	message msg;
	int r;
	int irq_set;
	int kbd_hook_id;

	unsigned long scan_code;

	kbd_hook_id =keyboard_subscribe_int();
	if(kbd_hook_id == -1)
	{
		printf("keyboard_subscribe_int function failed! \n");
		return 1;
	}

	irq_set = BIT(kbd_hook_id);

	while(scan_code != -1) {
			/* Get a request message. */
			if ( (r=driver_receive(ANY, &msg, &ipc_status)) !=0 ) {
				printf("driver_receive failed with: %d", r);
				continue;
			}
			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
						{
							if(ass==0)
							scan_code = keyboard_int_handler();
						}

						break;
				default:
					break; /* no other notifications expected: do nothing */
					}
				}
			} else { /* received a standard message, not a notification */
				/* no standard messages expected: do nothing */
			}
			if(scan_code == -1)
				break;
	}


	if(keyboard_unsubscribe_int() == 0)
		return 0;
	else
	{
		printf("keyboard_unsubscribe_int function failed! \n");
		return 1;
	}

}
int kbd_test_leds(unsigned short n, unsigned short *leds) {
    /* To be completed */
}
int kbd_test_timed_scan(unsigned short n) {

}
