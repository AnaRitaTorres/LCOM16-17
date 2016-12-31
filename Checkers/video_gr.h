#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H


#include "rectangle.h"
#include "sprite.h"

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */



#define SWAP(X,Y) { \
       int temp = X ; \
       X = Y ; \
       Y = temp ; \
    } /**< @brief Swap values */



/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);


/**
* @brief Draw a pixel
*
* @param x posicao x do pixel
* @param y posicao y do pixel
* @param color cor do pixel
* @param buf buffer onde se desenha
*/
void draw_pixel(unsigned int x, unsigned int y, int color, char* buf);

/**
* @brief Desenha um retangulo
*
* @param xi x inicial do retangulo
* @param yi Y inicial do retangulo
* @param xf X tamanho do comprimento do retangulo
* @param yf Y tamanho da altura do retangulo
* @param color cor do retangulo
* @param buf buffer onde se desenha
* @return validacao
*/
int draw_rectangle(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, int color,char* buf);

/**
* @brief Desenha um circulo
*
* @param x0 X centro do circulo
* @param y0 Y centro do circulo
* @param radius raio do circulo
* @param color cor do circulo
* @param buf buffer onde se desenha
*/
void draw_circle(int x0, int y0, int radius, int color, char* buf);

/**
* @brief Faz visualizar um circulo
*
* @param x0 X centro do circulo
* @param y0 Y centro do circulo
* @param radius raio do circulo
* @param color cor do circulo
* @param buf buffer onde se desenha
*/
void see_circle(int x0, int y0, int radius, int color, char* buf);

/**
* @brief copia os graficos do buffer2 para a  Video Mem
*
*/
void flipScreen2();
/**
* @brief copia os graficos do buffer1 para a  Video Mem
*
*/
void flipScreen1();

/**
* @brief limpa o ecra
*
*/
void cleanScreen();


/**
* @brief Get da resolucao horizontal
*
* @return resolucao horizontal
*/
unsigned getH_res();
/**
* @brief Vai buscar a resolucao vertical
*
* @return resolucao vertical
*/
unsigned getV_res();

/**
* @brief Cria uma cor especifica
*
* @param r faccao de vermelho
* @param g fraccao de verde
* @param b fraccao de azul
* @return cor resultante
*/
int rgb(unsigned char r, unsigned char g, unsigned char b);

/**
* @brief Vai buscar os graficos da video mem
*
* @return retorna graficos da video mem
*
*/
char *getVideoMem();
/**
* @brief Vai buscar os graficos do buffer1
*
* @return retorna graficos do buffer1
*
*/
char *getBuffer1();
/**
* @brief Vai buscar os graficos do buffer2
*
* @return retorna graficos do buffer2
*
*/
char *getBuffer2();

#endif /* __VIDEO_GR_H */

