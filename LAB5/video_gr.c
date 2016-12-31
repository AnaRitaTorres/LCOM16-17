#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "video_gr.h"
#include "vbe.h"
#include "lmlib.h"
#include "pixmap.h"
#include "sprite.h"
/* Private global variables */

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */


void *vg_init(unsigned short mode){

	struct reg86u r;
	r.u.w.ax = SET_VBE_MODE;
	r.u.w.bx = (1<<14) | mode;
	r.u.b.intno = VBE_INTERRUPT;

	unsigned vram_size;
	vbe_mode_info_t vbe_info;
	struct mem_range mr;



	if (sys_int86(&r) != OK){
		printf("\tvg_init(): sys_int86() failed \n");
		return NULL;
	}
	else {

		if(vbe_get_mode_info(mode, &vbe_info) != 0){
			printf("vbe_get_mode_info function failed! \n");
			return NULL;
		}

		else{
			bits_per_pixel = vbe_info.BitsPerPixel;
			h_res = vbe_info.XResolution;
			v_res = vbe_info.YResolution;

			/* Allow memory mapping */
			vram_size = (h_res * v_res * bits_per_pixel);
			mr.mr_base = (phys_bytes) vbe_info.PhysBasePtr;
			mr.mr_limit = mr.mr_base + vram_size;


			if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)){
				panic("sys_privctl (ADD_MEM) failed: %d\n", r);
				return NULL;
			}

			/* Map memory */

			video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

			if(video_mem == MAP_FAILED){
				panic("couldn't map video memory");
				return NULL;
			}

			return video_mem;
		}

	}

	return video_mem;

}

int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = VBE_INTERRUPT; /* BIOS video services */
	reg86.u.b.ah = VBE_VIDEO_MODE;    /* Set Video Mode function */
	reg86.u.b.al = SET_TEXT_MODE;    /* 80x25 text mode*/

	if( sys_int86(&reg86) != OK ){
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}

int set_color(unsigned short x, unsigned short y, unsigned long color ) {

		char* buffer = video_mem;

		buffer = buffer + ((y*H_RES + x)*BITS_PER_PIXEL/8);
		*buffer=color;

		return 0;

}

int check_screen(unsigned short xi, unsigned short yi,
		unsigned short xf, unsigned short yf){

	if (xi < 0 || xi > H_RES){
		printf("xi value is invalid! \n");
		return 1;
	}
	else if(yi < 0 || yi > V_RES){
		printf("yi value is invalid! \n");
		return 1;
	}
	else if(xf < 0 || xf > H_RES){
		printf("fx value is invalid! \n");
		return 1;
	}
	else if(yf <0 || yf > V_RES){
		printf("yf value is invalid! \n");
		return 1;
	}
	else
		return 0;
}

int draw_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color){

		if( x < 0 || x + size> H_RES){
			printf("x value is invalid! \n");
			return 1;
		}
		else if(y < 0 || y + size> V_RES){
			printf("y value is invalid! \n");
			return 1;
		}
		else if(color == 0){
			printf("color value is invalid! \n");
			return 1;
		}

		unsigned short column = x;
		//first and second line
		for(column; column <= x + size; column++){
			set_color(column, y,color);
			set_color(column, y + size,color);
		}

		unsigned short line = y ;
		//first column and second
		for(line; line <= y + size; line++){
			set_color(x , line,color);
			set_color(x + size, line, color);
		}

		return 0;


}

int draw_line(unsigned short xi, unsigned short yi,
		unsigned short xf, unsigned short yf, unsigned long color){


	if (check_screen(xi, yi, xf, yf)!=0)
		return 1;

	else if(color == 0){
		printf("color value is invalid! \n");
		return 1;
	}

	//DDA algorithm

	float deltaX = xf - xi;
	float deltaY = yf - yi;
	float slope = deltaY/deltaX;
	unsigned int i;
	float x, y, steps, Xincrement, Yincrement;
	x = xi, y = yi;

	if (slope > 1) {
		if (fabs(deltaX) > fabs(deltaY))
			steps = abs(deltaX);
		else
			steps = abs(deltaY);
		}
		else {
			if (fabs(deltaY) > fabs(deltaX))
				steps = abs(deltaY);
			else
				steps = abs(deltaX);
		}

		Xincrement = deltaX / steps;
		Yincrement = deltaY / steps;

		for (i = 0; i < steps; i++) {
			if (set_color(x, y, color) != 0)
				return 1;
			x = x + Xincrement;
			y = y + Yincrement;
		}

	return 0;

}

double check_movement(unsigned short hor, short delta, unsigned short time, double xspeed, double yspeed){

	if(hor==0){

		yspeed = (double)delta/(double)time *(double)(1.0/STANDARD_FREQ);
		xspeed=0;
		return 0;
	}
	else if(hor!=0){

		xspeed = (double)delta/(double)time *(double)(1.0/STANDARD_FREQ);
		yspeed=0;
		return 0;
	}
	else
		return 1;
}
