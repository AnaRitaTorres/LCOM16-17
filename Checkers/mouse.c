#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "i8042.h"
#include "mouse.h"
#include "video_gr.h"
#include "rectangle.h"
#include "keyboard.h"

static int hook_id_mouse;
static int counter;
unsigned char mouse_packets[PACKET_SIZE];
unsigned char mouse_config[PACKET_SIZE];

Mouse* mouse = NULL;

void newMouse() {
	mouse = (Mouse*) malloc(sizeof(Mouse));

	counter=0;
	mouse->x = 150;
	mouse->y = 150;
	mouse->xSign = 0;
	mouse->ySign = 0;
	mouse->deltaX = 0;
	mouse->deltaY = 0;
	mouse->leftButton = 0;
	mouse->middleButton = 0;
	mouse->rightButton = 0;
	mouse->color = 3;
	mouse->rect = newRectangle(mouse->x, mouse->y, 10, 10);
}

Mouse* getMouse() {
	if (!mouse)
		newMouse();
	return mouse;
}

void setMouseColor(int color){
	mouse->color = color;
}

void drawMouse() {
	drawRectangle(mouse->rect, mouse->color, getVideoMem());
}

void deleteMouse() {
	deleteRectangle(mouse->rect);
	free(mouse);
}

void resetMouse(){
	mouse->x = 0.15 * getH_res();
	mouse->y = 0.55 * getV_res();
}

int mouse_outH(int aux)
{
	if (aux > 590)
		return 590;
	else if (aux < 0)
		return 0;
	else
		return aux;
}

int mouse_outV(int aux)
{
	if (aux > getV_res() - 10)
		return getV_res() - 10;
	else if (aux < 0)
		return 0;
	else
		return aux;
}

int clickedMouse() {
	if (mouse->leftButton)
		return 1;
	else
		return 0;
}

unsigned int bit(int bit, unsigned long byte){
	return ((byte & (1 << bit)) >> bit);
}

void update_mouse() {
			mouse->xSign = bit(4,mouse_packets[0]);
			mouse->ySign = bit(5,mouse_packets[0]);
			if (mouse->ySign)
				mouse->deltaY = (char)mouse_packets[2]; // | 0xFF00;
			else
				mouse->deltaY =mouse_packets[2];
			if (mouse->xSign)
				mouse->deltaX = (char)mouse_packets[1];// | 0xFF00;
			else
				mouse->deltaX = mouse_packets[1];
			mouse->x = mouse_outH(mouse->x + mouse->deltaX);
			mouse->y = mouse_outV(mouse->y - mouse->deltaY);
			mouse->leftButton = bit(0,mouse_packets[0]);
			mouse->middleButton = bit(2,mouse_packets[0]);
			mouse->rightButton = bit(1,mouse_packets[0]);
			setRecLocation(mouse->rect, mouse->x, mouse->y);
}

int handle_mouse() {

	unsigned long data;
	mouse_read_cmd_kbd(&data);
	mouse_packets[counter] = data;

	if (counter == 0 && !(BIT(3) & mouse_packets[0]))
		return;

	counter = (counter + 1) % 3;
	if (counter != 0)
		return;

	update_mouse();

	return 0;
}

void mouse_set_package(){

	//SET LEFT BUTTON
	unsigned int bit0 = bit(0, mouse_packets[0]);
	if (bit0 == 0)
		bit0 = 0;
	else
		bit0 = 1;

	//SET RIGHT BUTTON
	unsigned int bit1 = bit(1, mouse_packets[0]);
	if (bit1 == 0 )
		bit1 = 0;
	else
		bit1 = 1;

	//SET MIDDLE BUTTON
	unsigned int bit2 = bit(2, mouse_packets[0]);
	if (bit2== 0)
		bit2 = 0;
	else
		bit2 = 1;

	//SET X SIGN
	unsigned int bit4 = bit(4, mouse_packets[0]);
	if (bit4 == 0)
		bit4= 0;
	else
		bit4 = 1;

	////SET X DELTA
	if (bit4 == 1) {
		mouse_packets[1] =  mouse_packets[1]|~((1 << 18) - 1);  //conversao do complemento para 2
	}
	else
		mouse_packets[1] = (short) mouse_packets[1];

	//SET Y SIGN
	unsigned int bit5 = bit(5, mouse_packets[0]);
	if (bit5 == 0)
		bit5 = 0;
	else
		bit5 = 1;

	//SET Y DELTA
	if (bit5 == 1){
		mouse_packets[2] = mouse_packets[2] |~((1 << 18) - 1);
	}
	else
		mouse_packets[2] = (short) mouse_packets[2];

	//SET X OVERFLOW
	unsigned int bit6 = bit(6, mouse_packets[0]);
	if (bit6 == 0)
		bit6 = 0;
	else
		bit6 = 1;

	//SET Y OVERFLOW
	unsigned int bit7 = bit(7, mouse_packets[0]);
	if (bit7 == 0)
		bit7 = 0;
	else
		bit7 = 1;
}

int mouse_get_packet() {

	unsigned long byte;
	static int byte_counter = 0;

	byte = mouse_read_cmd_kbd(&byte);
	if(byte == -1){
		return 1;
	}
	unsigned int bit3 = bit(3,byte);
	if(byte_counter == 0 && (!((bit3) && (byte != ACK)))){
		return 1;
	}

	int index = (byte_counter % PACKET_SIZE);

	mouse_packets[index] = (unsigned char )byte;

	byte_counter++;

	if (index == 0) {
		mouse_set_package();
		return 0;
	}
	else{
			return 1;
	}

	return 0;
}

int mouse_write_cmd_kbd(unsigned long command) {
	unsigned long stat;
	unsigned int i;

	for (i = 0; i < NUMBER_TRIES; i++)
	{
		if(sys_inb(STAT_REG, &stat)!=OK)
		{
			printf("sys_inb function failed!\n");
			return -1;
		}

		while (!(stat & INPUT_BUFFER_FULL))
		{

			if(sys_outb(KBD_CMD_REG, command)!=OK)
			{
				printf("sys_outb function failed! \n");
				return -1;
			}
			return 0;

		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int mouse_read_cmd_kbd(unsigned long *command){

	if(sys_inb(KBD_CMD_REG, command)!=OK){
		printf("sys_inb function failed! \n");
		return -1;
	}
	return 0;
}

int mouse_write_cmd_kbc(unsigned long command) {
	unsigned long stat;

	unsigned int i;
	for (i=0; i < NUMBER_TRIES; i++)
	{
		if(sys_inb(STAT_REG, &stat)!=OK)
		{
			printf("sys_inb function failed!\n");
			return -1;
		}

		while (!(stat & INPUT_BUFFER_FULL))
		{

			if(sys_outb(KBC_CMD_REG, command)!=OK)
			{
				printf("sys_outb function failed! \n");
				return -1;
			}
			return 0;
		}

		tickdelay(micros_to_ticks(DELAY_US));
	}


}

unsigned long mouse_read_resp() {
	unsigned long stat;
	unsigned long data;
	unsigned int i;
	for (i = 0; i < NUMBER_TRIES; i++)
	{
		if(sys_inb(STAT_REG, &stat)!=OK)
		{
			printf("sys_inb function failed!\n");
			return -1;
		}
		while (stat & OUTPUT_BUFFER_FULL)
		{

			if(sys_inb(OUT_BUF, &data)!=OK)
			{
				printf("sys_inb function failed!\n");
				return -1;
			}
			if ((stat &(PARITY|TIMEOUT)) == 0){
				return data;
			}
			else
				return -1;

		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
}

int mouse_write_config(unsigned long cmd) {
	unsigned int i;
	unsigned long data1;
	unsigned long data;
	for(i =0 ;i < NUMBER_TRIES; i++) {

		if(mouse_write_cmd_kbc(MOUSE_CMD_REG) == -1) {
			printf("mouse_write_cmd_kbc(MOUSE_CMD_REG) function failed! \n");
			return 1;
		}
		data1 = mouse_read_resp();
		if(data1 == -1)
		{
			printf("mouse_read_resp function failed! \n");
			return 1;
		}

		if(mouse_write_cmd_kbd(cmd)==-1){
			printf("mouse_write_cmd_kbd(cmd) function failed! \n");
			return 1;
		}

		data = mouse_read_resp();
		if(data == -1)
		{
			printf("mouse_read_resp function failed! \n");
			return 1;
		}
		else if(data == ACK)
		{
			return 0;
		}
	}

	printf("Way too many tries! \n");
	return 1;
}

int mouse_set_stream_mode(){

	if(mouse_write_config(SET_STREAM_MODE) != 0)
	{
		printf("mouse_write_config(SET_STREAM_MODE) function failed! \n");
		return 1;
	}

	if(mouse_write_config(ENABLE) != 0)
	{
		printf("mouse_write_config(ENABLE) function failed! \n");
		return 1;
	}

	return 0;
}

int mouse_subscribe_int() {

	hook_id_mouse = IRQ_MOUSE;

	if (sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse) == OK){
		if(sys_irqenable(&hook_id_mouse) == OK){
			mouse_set_stream_mode();
			return BIT(IRQ_MOUSE);
		}

		else{
			printf("Sys_irqenable failed!\n");
			return -1;
		}

	}
	else{
		printf("Sys_irqserpolicy failed!\n");
		return -1;
	}

}

int mouse_unsubscribe_int() {

	if(sys_irqrmpolicy(&hook_id_mouse) == OK)
		if (sys_irqdisable(&hook_id_mouse) == OK)
			return 0;
		else{
			printf("Sys_irqdisable failed!\n");
			return -1;
		}

	else{
		printf("Sys_irqrmpolicy failed!\n");
		return -1;
	}
}




