#include "mouse.h"


static int hook_id_mouse;
unsigned char mouse_packets[PACKET_SIZE];
unsigned char mouse_config[PACKET_SIZE];

int mouse_subscribe_int() {
	hook_id_mouse = IRQ_MOUSE;
	if (sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE|IRQ_EXCLUSIVE, &hook_id_mouse) != OK)
	{
		printf("Sys_irqserpolicy failed!\n");
		return -1;
	}
	else
	{
		return IRQ_MOUSE;
	}
}

int mouse_unsubscribe_int() {
	if(sys_irqrmpolicy(&hook_id_mouse) == OK)
	{
		return 0;
	}
	else
	{
		printf("Sys_irqrmpolicy failed!\n");
		return -1;
	}
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

unsigned long read_from_buffer(){
	unsigned long byte;
	if(sys_inb(OUT_BUF, &byte) != OK)
	{
		printf("sys_inb(OUT_BUF) function failed! \n");
		return -1;
	}
	else {
		return byte;
	}
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

int mouse_dis_stream_mode() {
	if(mouse_write_config(DISABLE) != 0)
	{
		printf("mouse_write_config(DISABLE) function failed! \n");
		return 1;
	}
	return 0;
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


unsigned int bit(int bit, unsigned long byte)
{
	return ((byte & (1 << bit)) >> bit);

}

void mouse_set_package() {

	//set left button bit
	unsigned int bit0 = bit(0, mouse_packets[0]);
	if (bit0 == 0)
		bit0 = 0;
	else
		bit0 = 1;

	//set right button bit
	unsigned int bit1 = bit(1, mouse_packets[0]);
	if (bit1 == 0 )
		bit1 = 0;
	else
		bit1 = 1;

	//set middle button bit
	unsigned int bit2 = bit(2, mouse_packets[0]);
	if (bit2== 0)
		bit2 = 0;
	else
		bit2 = 1;

	//set x sign bit
	unsigned int bit4 = bit(4, mouse_packets[0]);
	if (bit4 == 0)
		bit4= 0;
	else
		bit4 = 1;

	//set x delta
	if (bit4 == 1) {
		mouse_packets[1] =  mouse_packets[1]|~((1 << 18) - 1);  //conversao do complemento para 2
	}
	else
		mouse_packets[1] = (short) mouse_packets[1];

	//set y sign bit
	unsigned int bit5 = bit(5, mouse_packets[0]);
	if (bit5 == 0)
		bit5 = 0;
	else
		bit5 = 1;

	//set y delta
	if (bit5 == 1){
		mouse_packets[2] = mouse_packets[2] |~((1 << 18) - 1);
	}
	else
		mouse_packets[2] = (short) mouse_packets[2];

	//set x overflow bit
	unsigned int bit6 = bit(6, mouse_packets[0]);
	if (bit6 == 0)
		bit6 = 0;
	else
		bit6 = 1;

	//set y overflow bit
	unsigned int bit7 = bit(7, mouse_packets[0]);
	if (bit7 == 0)
		bit7 = 0;
	else
		bit7 = 1;

	printf("B1=0x%02X B2=0x%02X  B3=0x%02X   LB=%d   MB=%d   RB=%d   XOV=%d   YOV=%d   X=%d   Y=%d\n",mouse_packets[0],mouse_packets[1],mouse_packets[2],bit0,bit2,bit1,
			bit6,bit7, mouse_packets[1], mouse_packets[2]);


}

int mouse_get_packet() {

	unsigned long byte;
	static int byte_counter = 0;

	byte = read_from_buffer();
	if(byte == -1)
	{
		return 1;
	}
	unsigned int bit3 = bit(3,byte);
	if(byte_counter == 0 && (!((bit3) && (byte != ACK))))
		{
			return 1;
		}

		int index = (byte_counter % PACKET_SIZE);

		mouse_packets[index] = (unsigned char )byte;

		byte_counter++;

		if (index == 0) {
			mouse_set_package();
			return 0;
		}
		else {
			return 1;
		}

		return 0;
}

void mouse_set_config()
{
	//SET LEFT BUTTON
	unsigned int bit0 = bit(0, mouse_config[0]);

	if(bit0)
		printf("Left Button active \n");
	else
		printf("Left Button inactive \n");

	//SET RIGHT BUTTON
	unsigned int bit1 = bit(1, mouse_config[0]);


	if(bit1)
		printf("Right Button active \n");
	else
		printf("Right Button inactive \n");

	//SET MIDDLE BUTTON
	unsigned int bit2 = bit(2, mouse_config[0]);


	if(bit2)
		printf("Middle Button active \n");
	else
		printf("Middle Button inactive \n");


	//SET SCALING
	unsigned int bit4 = bit(4, mouse_config[0]);

	if(bit4)
		printf("Scaling 2:1 \n");
	else
		printf("Scaling 1:1 \n");

	//SET ENABLE
	unsigned int bit5 = bit(5, mouse_config[0]);
	if(bit5)
		printf("Data reporting enabled \n");
	else
		printf("Data reporting disabled \n");

	//SET REMOTE
	unsigned int bit6 = bit(6, mouse_config[0]);


	if(bit6)
		printf("Remote polled mode \n");
	else
		printf("Remote stream mode \n");

	//SET RESOLUTION
	mouse_config[1] =  mouse_config[1] & (BIT(0)|BIT(1));
	if(mouse_config[1] == 00)
		printf("Resolution of 1 count per mm \n");
	else if(mouse_config[1] == 01)
		printf("Resolution of 2 count per mm \n");
	else if(mouse_config[1] == 02)
		printf("Resolution of 4 count per mm \n");
	else if(mouse_config[1] == 03)
		printf("Resolution of 8 count per mm \n");

	printf("Sample Rate: %d \n", mouse_config[2]);
}

int mouse_get_config()
{
	unsigned long data;
	unsigned int index;
	for(index = 0; index < 3; index++)
	{
		data = mouse_read_resp();
		if(data == -1)
		{
			printf("mouse_read_resp function failed! \n");
			return 1;
		}

		mouse_config[index] = (char) data;
	}

	mouse_set_config();
	return 0;

}

int handle_mouse(int length){

	ev_t evt;

	if (mouse_get_packet()==1)
		return 1;

	//right button
	if(bit(1,mouse_packets[0])){

		evt.type=RDOW;

		if (check_line(&evt, length) == 0)
			return 0;
	}
	else{

		evt.type=RUP;

		if (check_line(&evt, length) == 0)
			return 0;
	}

	if(mouse_packets[1]!=0 && mouse_packets[2]!=0){
			evt.type = MOVE;

			if (check_line(&evt, length) ==0)
				return 0;
		}

	return 1;
}

int check_line(ev_t *evt, int length){

	static state_t st = INIT; // initial state; keep state
	int hor_l=0,vert_l=0;

	switch (st) {
	case INIT:
		if(evt->type == RDOW){
			st = DRAW;
		}
		break;

	case DRAW:
		if(evt->type == MOVE){

			if (length*mouse_packets[2] < 0){
				vert_l=0;
				hor_l+= mouse_packets[1];
			}
			else{
				vert_l+=length;
				hor_l+= mouse_packets[1];
			}


			if (abs(vert_l) >= abs(length)){
				st = COMP;
				return 0;
			}


		}
		else if( evt->type == RUP){
			st = INIT;
		}
		break;

	default:
		break;
	}

	return -1;
}
