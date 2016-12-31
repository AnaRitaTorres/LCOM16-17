#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"
#include "i8042.h"


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




