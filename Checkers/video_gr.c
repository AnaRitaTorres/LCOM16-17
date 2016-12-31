#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "vbe.h"
#include "video_gr.h"
#include "i8042.h"

//Private global variables
static char *video_mem;			/* Process address to which VRAM is mapped */
static char *buffer1;
static char *buffer2;			/* Process address to auxiliary buffer */
static unsigned h_res;			/* Horizontal screen resolution in pixels */
static unsigned v_res;			/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel;


void* vg_init(unsigned short mode) {

	struct reg86u r;
	r.u.w.ax = SET_VBE_MODE;
	r.u.w.bx = BIT(14) | mode;
	r.u.b.intno = VBE_INTERRUPT;

	unsigned vram_size;
	vbe_mode_info_t vbe_info;
	struct mem_range mr;

	if (sys_int86(&r) != OK){
		printf("\tvg_init(): sys_int86() failed \n");
		return NULL;
	}
	else{

		if(vbe_get_mode_info(mode, &vbe_info) != 0){
			printf("vbe_get_mode_info function failed! \n");
			return NULL;
		}
		else{

			bits_per_pixel = vbe_info.BitsPerPixel;
			h_res = vbe_info.XResolution;
			v_res = vbe_info.YResolution;

			if (bits_per_pixel / 8 > 0)
				bytes_per_pixel = bits_per_pixel / 8;
			else
				bytes_per_pixel = 1;

			/* Allow memory mapping */
			vram_size = (h_res * v_res * bytes_per_pixel);
			mr.mr_base = (phys_bytes) vbe_info.PhysBasePtr;
			mr.mr_limit = mr.mr_base + vram_size;


			if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)){
				panic("sys_privctl (ADD_MEM) failed: %d\n", r);
				return NULL;
			}

			/* Map memory */

			video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
			buffer1 = malloc(vram_size);
			buffer2 = malloc(vram_size);


			if(video_mem == MAP_FAILED){
				panic("couldn't map video memory");
				return NULL;
			}

			return video_mem;
		}

	}
	return video_mem;

}

int vg_exit(){

	struct reg86u r;

	r.u.b.intno = VBE_INTERRUPT; /* BIOS video services */
	r.u.b.ah = VBE_VIDEO_MODE;    /* Set Video Mode function */
	r.u.b.al = SET_TEXT_MODE;    /* 80x25 text mode*/

	if(sys_int86(&r) != OK ){
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	}
	else
		return 0;
}

void draw_pixel(unsigned int x, unsigned int y, int color, char* buf) {
	if (color != BLACK) {
		int i;
		char* vptr;

		if (x > h_res || y > v_res) {
			return;
		}

		i = (y * h_res + x) * bytes_per_pixel;

		vptr = &buf[i];

		for (i = 0; i < bytes_per_pixel; i++) {
			*vptr = (char) color;
		}
	}
}


int draw_rectangle(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, int color, char* buf) {

	if (xf < xi) {
		SWAP(xi, xf);
	}

	if (yf < yi) {
		SWAP(yi, yf);
	}

	unsigned short x, y;

	for (x = xi; x < xf; x++) {
		for (y = yi; y < yf; y++) {
			draw_pixel(x, y, color, buf);
		}
	}
}

// algoritmo http://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
void draw_circle(int x0, int y0, int radius, int color, char* buf) {
	int x = radius;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;
	int i;
	while (x >= y) {
		for (i = x0 - x; i <= x0 + x; i++) {
			draw_pixel(i, y0 + y, color, buf);
			draw_pixel(i, y0 - y, color, buf);
		}
		for (i = x0 - y; i <= x0 + y; i++) {
			draw_pixel(i, y0 + x, color, buf);
			draw_pixel(i, y0 - x, color, buf);
		}

		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0) {
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

void see_circle(int x0, int y0, int radius, int color,char* buf) {
	int x = radius;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;
	int i, j;
	for (i = 0; i < y0-x; i++)
		for (j = 0; j < h_res; j++)
			draw_pixel(j, i, color, buf);
	for (i = y0+x; i < v_res; i++)
		for (j = 0; j < h_res; j++)
			draw_pixel(j, i, color, buf);
	while (x >= y) {
		for (i = 0; i <= x0 - x; i++) {
			draw_pixel(i, y0 + y, color, buf);
			draw_pixel(i, y0 - y, color, buf);
		}
		for (i = x0 + x; i <= getH_res(); i++) {
			draw_pixel(i, y0 + y, color, buf);
			draw_pixel(i, y0 - y, color, buf);
		}
		for (i = 0; i <= x0 - y; i++) {
			draw_pixel(i, y0 + x, color, buf);
			draw_pixel(i, y0 - x, color, buf);
		}
		for (i = x0 + y; i <= getH_res(); i++) {
			draw_pixel(i, y0 + x, color, buf);
			draw_pixel(i, y0 - x, color, buf);
		}

		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0) {
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

void flipScreen2(){
	memcpy(video_mem, buffer2, h_res * v_res * bytes_per_pixel);
}

void flipScreen1(){
	memcpy(video_mem, buffer1, h_res * v_res * bytes_per_pixel);
}

void cleanScreen() {
	memset(video_mem, 0,  h_res * v_res * bytes_per_pixel);
}

unsigned getH_res() {
	return h_res;
}

unsigned getV_res() {
	return v_res;
}

int rgb(unsigned char r, unsigned char g, unsigned char b) {

	if (r < 0 || 255 < r || g < 0 || 255 < g || b < 0 || b > 255)
		return -1;
	int red = r * 31 / 255;
	int green = g * 63 / 255;
	int blue = b * 31 / 255;

	return (red << 11) | (green << 5) | blue;
}


char *getVideoMem(){
	return video_mem;
}

char *getBuffer1(){
	return buffer1;
}

char *getBuffer2(){
	return buffer2;
}


