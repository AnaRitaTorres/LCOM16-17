#include "sprite.h"
#include <stdlib.h>
#include "video_gr.h"
#include "numberxpm.h"



Sprite *create_sprite(char *pic[],int x, int y, double xspeed, double yspeed){

	//allocate space for the "object"
	Sprite *sp = malloc (sizeof(Sprite));

	if( sp == NULL)
		return NULL;

	// read the sprite pixmap
	sp->map = (char*)read_xpm(pic, &(sp->width), &(sp->height));

	if( sp->map == NULL){
		free(sp);
		return NULL;
	}

	sp->x=x;
	sp->y=y;
	sp->xspeed=xspeed;
	sp->yspeed=yspeed;

	return sp;
}

void destroy_sprite(Sprite *sp){
	if( sp == NULL )
		return;
	free(sp->map);
	free(sp);
	sp = NULL;
}


int draw_xpm(Sprite *sp){

	int i,j;

	for (i = 0; i < sp->height; i++) {
		for (j = 0; j < sp->width; ++j) {
			draw_pixel((unsigned int) (j + sp->x), (unsigned int) (i + sp->y), sp->map[i*sp->width + j], getVideoMem());
		}
	}
	return 0;
}

