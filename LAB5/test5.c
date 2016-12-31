#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include "timer.h"
#include "vbe.h"
#include "video_gr.h"
#include "sprite.h"
#include <minix/syslib.h>
#include <minix/drivers.h>


void *test_init(unsigned short mode, unsigned short delay) {

	char* video_mem;

	video_mem = vg_init(mode);
	if (video_mem == NULL){
		printf("vg_init function failed! \n");
		return NULL;
	}

	int ipc_status;
	message msg;
	int freq =60;
	int r;
	int irq_set;
	int bit_hook_id;
	int counter = 0;

	bit_hook_id = timer_subscribe_int();
	if(bit_hook_id  == -1)
	{
		printf("Timer_subscribe_int function failed! \n");
		return NULL;
	}

	irq_set = BIT(bit_hook_id);



	while(counter < delay * freq) {
		if ( (r=driver_receive(ANY, &msg, &ipc_status)) !=0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set) {

					counter++;
				}
				break;
			default:
				break;
			}
		} else {

		}
	}

	vbe_mode_info_t vmi_p;
	if(vbe_get_mode_info(mode, &vmi_p)){
		vg_exit();
		return NULL;
	}

	if(vg_exit() != 0)
	{
		printf("vg_exit function failed!\n");
		return NULL;
	}

	if(timer_unsubscribe_int() != 0)
	{
		printf("Timer_unsubscribe_int function failed! \n");
		return NULL;
	}

	printf("Physical address: 0x%X \n",vmi_p.PhysBasePtr);
	return video_mem;

}


int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

		if (vg_init(MODE_1024x768) == NULL){
			printf("vg_init function failed! \n");
			return 1;
		}


		if(draw_square(x,y,size,color) != 0){
			printf("draw_square function failed! \n");
			vg_exit();
			return 1;
		}


		int ipc_status;
		message msg;
		int r;
		int irq_set;
		int kbd_hook_id;

		int resp;
		kbd_hook_id =keyboard_subscribe_int();
		if(kbd_hook_id == -1){
			printf("keyboard_subscribe_int function failed! \n");
			return 1;
		}

		irq_set = BIT(kbd_hook_id);

		while(1) {
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
								resp = keyboard_scan_c();
							}

							break;
					default:
						break; /* no other notifications expected: do nothing */
						}
					}
				} else { /* received a standard message, not a notification */
					/* no standard messages expected: do nothing */
				}
				if(resp == -1)
					break;
		}


		if(vg_exit() != 0)
		{
			printf("vg_exit function failed!\n");
			return 1;
		}

		if(keyboard_unsubscribe_int() == 0)
			return 0;
		else
		{
			printf("keyboard_unsubscribe_int function failed! \n");
			return 1;
		}


}

int test_line(unsigned short xi, unsigned short yi, 
		unsigned short xf, unsigned short yf, unsigned long color) {

	if (vg_init(MODE_1024x768) == NULL){
		printf("vg_init function failed! \n");
		return 1;
	}

	if(draw_line(xi,yi,xf,yf,color)!=0){
		printf("test_line function failed! \n");
		vg_exit();
		return 1;
	}

	int ipc_status;
	message msg;
	int r;
	int irq_set;
	int kbd_hook_id;

	int resp;
	kbd_hook_id =keyboard_subscribe_int();
	if(kbd_hook_id == -1){
		printf("keyboard_subscribe_int function failed! \n");
		return 1;
	}

	irq_set = BIT(kbd_hook_id);

	while(1) {
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
						resp = keyboard_scan_c();
					}

					break;
				default:
					break; /* no other notifications expected: do nothing */
					}
				}
		} else { /* received a standard message, not a notification */
						/* no standard messages expected: do nothing */
		}
			if(resp == -1)
				break;
		}


		if(vg_exit() != 0){
			printf("vg_exit function failed!\n");
			return 1;
		}

		if(keyboard_unsubscribe_int() == 0)
			return 0;
		else{
			printf("keyboard_unsubscribe_int function failed! \n");
			return 1;
		}

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {

	Sprite *sp=create_sprite(xpm,xi,yi,0,0);

	if(sp==NULL){
		printf("create_sprite function failed! \n");
		return 1;
	}

	if (vg_init(MODE_1024x768) == NULL){
			printf("vg_init function failed! \n");
			return 1;
	}

	if(draw_xpm(sp)!=0){
		printf("draw_xpm function failed! \n");
		vg_exit();
		return 1;
	}

	int ipc_status;
	message msg;
	int r;
	int irq_set;
	int kbd_hook_id;

	int resp;
	kbd_hook_id =keyboard_subscribe_int();
	if(kbd_hook_id == -1){
		printf("keyboard_subscribe_int function failed! \n");
		return 1;
	}

		irq_set = BIT(kbd_hook_id);

		while(1) {
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
							resp = keyboard_scan_c();
						}

						break;
					default:
						break; /* no other notifications expected: do nothing */
						}
					}
			} else { /* received a standard message, not a notification */
							/* no standard messages expected: do nothing */
			}
				if(resp == -1)
					break;
			}


			if(vg_exit() != 0){
				printf("vg_exit function failed!\n");
				return 1;
			}

			if(keyboard_unsubscribe_int() == 0)
				return 0;
			else{
				printf("keyboard_unsubscribe_int function failed! \n");
				return 1;
			}

}	

int test_move(unsigned short xi, unsigned short yi, char *xpm[], 
		unsigned short hor, short delta, unsigned short time) {

	double xspeed=0,yspeed=0;

	if (vg_init(MODE_1024x768) == NULL){
		printf("vg_init function failed! \n");
		return 1;
	}


	timer_set_square(0,STANDARD_FREQ);

	int ipc_status;
	message msg;
	int r;
	int irq_set_kbd,irq_set_timer;
	int kbd_hook_id, timer_hook_id;
	int counter =0;

	int resp;
	timer_hook_id =timer_subscribe_int();
	kbd_hook_id =keyboard_subscribe_int();



	if(kbd_hook_id == -1){
		printf("keyboard_subscribe_int function failed! \n");
		return 1;
	}

	if(timer_hook_id ==-1){
		printf("timer_subscribe_int function failed! \n");
		return 1;
	}

	irq_set_kbd = BIT(kbd_hook_id);
	irq_set_timer = BIT(timer_hook_id);


	if(hor){
		xspeed = (double)delta/time;
		yspeed=0;

	}
	else{

		yspeed = (double)delta/time;
		xspeed=0;
	}

	Sprite *sp=create_sprite(xpm,xi,yi,xspeed,yspeed);

	if(sp==NULL){
		printf("create_sprite function failed! \n");
		return 1;
	}


	while(counter <= time* STANDARD_FREQ) {

		if ( (r=driver_receive(ANY, &msg, &ipc_status)) !=0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE:
					if(msg.NOTIFY_ARG & irq_set_timer){
						if(counter <= time* STANDARD_FREQ){
							counter++;


							if(erase_sprite(sp)!=0){
								printf("erase_sprite funtion failed! \n");
								return 1;
							}

							move_sprite(sp);


							if(draw_xpm(sp)!=0){
							    if(hor) {
							    	sp->y=yi;
							    	sp->x=1;
							    }
							    else  {
							    	sp->y=1;
							    	sp->x=xi;
							    }
							}
						}
					}
					if (msg.NOTIFY_ARG & irq_set_kbd)
					{
						resp = keyboard_scan_c();
					}

					break;
				default:
					break; /* no other notifications expected: do nothing */

				}
		}
		if(resp == -1)
			break;
	}


	destroy_sprite(sp);

	if(vg_exit() != 0){
		printf("vg_exit function failed!\n");
		return 1;
	}

	if(timer_unsubscribe_int()==0){

		if(keyboard_unsubscribe_int() == 0)
			return 0;
		else{
			printf("keyboard_unsubscribe_int function failed! \n");
			return 1;
		}
	}
	else{
		printf("timer_unsubscribe_int function failed! \n");
		return 1;
	}

}





int test_controller() {

	vbe_info_block vbe_block;
	uint16_t *ptr;
	ptr =vbe_get_info_block(&vbe_block);
	if(ptr == NULL){
		printf("vbe_get_info_block function failed! \n");
		return 1;
	}

	display_vbe_block_info(vbe_block,ptr);
	return 0;
}					

