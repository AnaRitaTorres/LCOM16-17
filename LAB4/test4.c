#include <minix/syslib.h>
#include <minix/drivers.h>
#include "test4.h"
#include "i8254.h"
#include "i8042.h"
#include "mouse.h"


int test_packet(unsigned short cnt){

	int mouse_hook_id;
	int ipc_status;
	message msg;
	int r;
	int irq_set;
	int c = 0;

	mouse_hook_id = mouse_subscribe_int();
	if(mouse_hook_id == -1)
	{
		printf("mouse_subscribe_int function failed! \n");
		return 1;
	}

	irq_set = BIT(mouse_hook_id);

	if(mouse_set_stream_mode() != 0)
	{
		printf("mouse_set_stream_mode function failed! \n");
		return 1;
	}

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
						if(mouse_get_packet()==0){
							c++;

						}
					}

					break;
			default:
				break; /* no other notifications expected: do nothing */
				}
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
		if (c >= cnt) {
			break;
		}
	}

	if(mouse_dis_stream_mode() != 0)
	{
		printf("mouse_dis_stream_mode function failed! \n");
		return 1;
	}

	if(mouse_unsubscribe_int() == 0){
		return 0;
	}
	else
	{
		printf("mouse_unsubscribe_int function failed! \n");
		return 1;
	}

	return 0;

}

int test_async(unsigned short idle_time) {
	int mouse_hook_id;
	int timer_hook_id;
	int ipc_status;
	message msg;
	int r;
	int timer_irq_set;
	int mouse_irq_set;
	int timedOut = 0;
	int resp=0;

	if (timer_set_square(STANDARD_TIMER, STANDARD_FREQ) == 1) {
		printf("timer_set_square function failed! \n");
		return 1;
	}

	timer_hook_id = timer_subscribe_int();
	if (timer_hook_id == -1) {
		printf("timer_subscribe_int function failed! \n");
		return 1;
	}
	timer_irq_set = BIT(timer_hook_id);

	mouse_hook_id = mouse_subscribe_int();
	if(mouse_hook_id == -1)
	{
		printf("mouse_subscribe_int function failed! \n");
		return 1;
	}

	mouse_irq_set = BIT(mouse_hook_id);

	if(mouse_set_stream_mode() != 0)
	{
		printf("mouse_set_stream_mode function failed! \n");
		return 1;
	}
	while (1) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & timer_irq_set) {
					timedOut++;
					if (timedOut % STANDARD_FREQ == 0){
						printf("Second %d without using mouse! \n",timedOut/STANDARD_FREQ);
					}
				}
				if (msg.NOTIFY_ARG & mouse_irq_set) {
					resp = mouse_get_packet();
					timedOut = 0;
				}
				break;
			default:
				break;
			}
		} else {
		}
		if (resp == -1) {
			break;
		}
		else if (timedOut >= idle_time * STANDARD_FREQ) {
			printf("Mouse packets timed Out! \n");
			break;
		}
	}

	if(mouse_dis_stream_mode() != 0)
	{
		printf("mouse_dis_stream_mode function failed! \n");
		return 1;
	}

	if (timer_unsubscribe_int() == 0)
		return 0;
	else {
		printf("timer_unsubscribe_int function failed! \n");
		return 1;
	}

	if(mouse_unsubscribe_int() == 0){
		return 0;
	}
	else
	{
		printf("mouse_unsubscribe_int function failed! \n");
		return 1;
	}

	return 0;

}

int test_config(void) {
	int mouse_hook_id;
	mouse_hook_id = mouse_subscribe_int();
	if(mouse_hook_id == -1)
	{
		printf("mouse_subscribe_int function failed! \n");
		return 1;
	}

	if(mouse_set_stream_mode() != 0)
	{
		printf("mouse_set_stream_mode function failed! \n");
		return 1;
	}

	if(mouse_write_config(STATUS_REQUEST) != 0)
	{
		printf("mouse_write_config(STATUS_REQUEST) function failed! \n");
		return 1;
	}

	if(mouse_get_config() != 0)
	{
		printf("mouse_get_config function failed! \n");
		return 1;
	}

	if(mouse_unsubscribe_int() == 0){
		return 0;
	}
	else
	{
		printf("mouse_unsubscribe_int function failed! \n");
		return 1;
	}
	if(mouse_dis_stream_mode() != 0)
	{
		printf("mouse_dis_stream_mode function failed! \n");
		return 1;
	}




}

int test_gesture(short length){

	int mouse_hook_id;
	int ipc_status;
	message msg;
	int r;
	int irq_set;
	int c = 0;

	mouse_hook_id = mouse_subscribe_int();
	if(mouse_hook_id == -1){

		printf("mouse_subscribe_int function failed! \n");
		return 1;
	}

	irq_set = BIT(mouse_hook_id);

	if(mouse_set_stream_mode() != 0){

		printf("mouse_set_stream_mode function failed! \n");
		return 1;
	}


	while(1){
		/*Get a request message.*/
		if ((r=driver_receive(ANY, &msg, &ipc_status)) !=0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if(is_ipc_notify(ipc_status)){
			if (_ENDPOINT_P(msg.m_source) == HARDWARE){
				if (msg.NOTIFY_ARG & irq_set){
					if(handle_mouse(length)==0){
						break;
					}
				}
			}
		}
	}



	if(mouse_dis_stream_mode() != 0){

		printf("mouse_dis_stream_mode function failed! \n");
		return 1;
	}

	if(mouse_unsubscribe_int() == 0){
		return 0;
	}
	else{

		printf("mouse_unsubscribe_int function failed! \n");
		return 1;
	}

	return 0;
}
