#ifndef __SPRITE_H
#define __SPRITE_H

#include "i8042.h"
#include "i8254.h"
#include "timer.h"
#include "keyboard.h"
#include "video_gr.h"

/** @defgroup sprite sprite
 * @{
 * Functions for sprite
 */

typedef struct {
	int x, y; // current position
	int width, height; // dimensions
	double xspeed, yspeed; // current speed
	char *map; // the pixmap
} Sprite;



/**
 * @brief Cria uma sprite
 *
 * @param pic apontador para o pixmap
 * @param xi posicao x inicial do pixmap
 * @param yi posicao y inicial do pixmap
 *
 * @return sprite do pixmap criado
 */
Sprite *create_sprite(char *pic[],int x, int y, double xspeed, double yspeed);

/**
 * @brief destroi uma sprite
 *
 * @param sp apontador para a sprite
 */
void destroy_sprite(Sprite *sp);

/**
 * @brief desenha um xpm no ecra
 *
 * @param sp apontador para a sprite
 *
 * @return inteiro 0 se for bem sucedido
 */
int draw_xpm(Sprite *sp);






#endif

