#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"



int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {

	mmap_t map;
	struct reg86u r;


	if(lm_init() == NULL){
		printf("lm_init function failed! \n");
		return 1;
	}

	map.virtual = lm_alloc(sizeof(map.size), &map);
	if (map.virtual ==  NULL) {
		printf("lm_alloc function failed\n");
		return 1;
	}



	r.u.b.intno = VBE_INTERRUPT;
	r.u.w.ax = VBE_MODE_INFO;
	r.u.w.cx = mode;
	r.u.w.es = PB2BASE(map.phys);
	r.u.w.di = PB2OFF(map.phys);



	if (sys_int86(&r) != OK) {
		printf("\tvg_init(): sys_int86() failed \n");
		return 1;
	}
	else
	{
		*vmi_p = *((vbe_mode_info_t*) map.virtual);
		lm_free(&map);
		return 0;


		if(r.u.b.ah == (FUNCTION_CALL_SUCCESSFUL) && r.u.b.al == VBE_FUNCTION)
		{
			*vmi_p = *((vbe_mode_info_t*) map.virtual);
			lm_free(&map);

			return 0;

		}

		if(r.u.b.ah == (FUNCTION_CALL_FAILED || FUNCTION_INVALID || FUNCTION_NOT_SUPPORTED)) {
			printf("Set Video Mode function failed! \n");
			return 1;
		}
	}

}

uint16_t* vbe_get_info_block(vbe_info_block *vbe_block)
{
	mmap_t map;
	struct reg86u r;

	if(lm_init() == NULL){
		printf("lm_init function failed! \n");
		return NULL;
	}

	if (lm_alloc(sizeof(vbe_info_block), &map)==  NULL) {
		printf("lm_alloc function failed\n");
		return NULL;
	}

	strcpy (vbe_block->VBEsignature, "VESA");
	r.u.w.ax = VBE_CONTROLLER_INFO;
	r.u.b.intno = VBE_INTERRUPT ; //0x10
	r.u.w.es = PB2BASE(map.phys);
	r.u.w.di = PB2OFF(map.phys);


	if (sys_int86(&r) != OK) {

		printf("\tvg_init(): sys_int86() failed \n");
		return NULL;

	}
	else {
		if(r.u.b.ah == (FUNCTION_CALL_FAILED || FUNCTION_INVALID || FUNCTION_NOT_SUPPORTED)) {
					printf("Set VBE controller info block failed! \n");
					lm_free(&map);
					return NULL;
		}
		if(r.u.b.ah == FUNCTION_CALL_SUCCESSFUL)
		{
			*vbe_block = *((vbe_info_block*) map.virtual);

			void* ptr = (void *)(PB2OFFBLOCK(vbe_block->VideoModePtr)>> 12);
			ptr += PB2OFF(vbe_block->VideoModePtr);
			ptr += PB2BASEBLOCK((uint32_t) map.virtual);
			lm_free(&map);

			return ptr;

		}
	}
}


void display_vbe_block_info(vbe_info_block vbe_block,uint16_t *ptr) {

	printf("\n              VBE BLOCK CAPABALITIES: \n\n");
	unsigned int Dac_bit = bit(DAC, (unsigned int)vbe_block.Capabilities);
	if(Dac_bit == 1)
	{
		printf("DAC width is switchable to 8 bits per primary color \n");
	}
	else
	{
		printf("DAC is fixed width, with 6 bits per primary color \n");
	}
	unsigned int Vga_bit = bit(VGA,(unsigned int)vbe_block.Capabilities);
	if(Vga_bit == 1)
	{
		printf("Controller is not VGA compatible \n");
	}
	else
	{
		printf("Controller is VGA compatible \n");
	}
	unsigned int Ramdac_bit = bit(RAMDAC, (unsigned int)vbe_block.Capabilities);
	if(Ramdac_bit == 1)
	{
		printf(" When programming large blocks of information to the RAMDAC, use the blank bit in Function 09h. \n");
	}
	else
	{
		printf("Normal RAMDAC operation \n");
	}
	printf("Modes supported: \n");

	while (*ptr != VIDEOPTR_FINAL)
	{
		printf("0x%02X\t", (unsigned short)*ptr);
		ptr += 1;
	}
	printf("\n");
	printf("VRAM memory has %d blocks of 64kb\n", vbe_block.TotalMemory);

}

unsigned int bit(int bit, unsigned long byte)
{
	return ((byte & (1 << bit)) >> bit);

}
