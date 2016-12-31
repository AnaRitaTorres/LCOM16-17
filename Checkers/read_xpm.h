#ifndef __XPM_H
#define __XPM_H

/** @defgroup read_xpm read_xpm
 * @{
 * Functions for read_xpm
 */


/**
 * @brief le um xpm
 *
 * @param map apontador para mapa
 * @param wd comprimento do mapa
 * @param ht altura do mapa
 *
 *  @return um char que corresponde a memoria alocada pelo pixmap
 */
char *read_xpm(char *map[], int *wd, int *ht);



#endif

