#pragma once

/** @defgroup mouse mouse
 * @{
 * Functions for mouse
 */

#include "rectangle.h"

typedef struct {
	int x, y; // especifica a posicao x e y
	    int xSign, ySign; // especifica o sinal de x e y
	    int deltaX, deltaY; //especifica a variacao de x e y
	    unsigned char packet[3]; // especifica os pacotes lidos pelos mouse

	    int leftButton; // especifica se o botao esquerdo foi pressionado
	    int middleButton; // especifica se o botao do meio foi pressionado
	    int rightButton; // especifica se o botao da direita foi pressionado

	    int color; // especifica a cor do retangulo
	    Rectangle* rect; // especifica o retangulo do mouse

} Mouse;



/**
 * @brief criar um  mouse novo
 *
 */
void newMouse();

/**
 * @brief Vai buscar o programa do mouse
 *
 * @return apontado nao nulo do mouse
 */
Mouse* getMouse();

/**
 * @brief muda a cor do mouse
 *
 * @param color nova cor
 */
void setMouseColor(int color);

/**
 * @brief desenha o mouse
 *
 */
void drawMouse();

/**
 * @brief apaga a mouse
 *
 */
void deleteMouse();

/**
 * @brief faz reset ao mouse
 *
 */
void resetMouse();

/**
 * @brief verifica se o mouse está fora da resolucao horizontal
 * não deixando ultrapassar esta resolucao
 *
 * @param valor inteiro que tem a posicao do rato
 *@return valor inteiro que diz a nova posicao do rato
 */
int mouse_outH(int aux);

/**
 * @brief verifica se o mouse está fora da resolucao vertical
 * não deixando ultrapassar esta resolucao
 *
 * @param valor inteiro que tem a posicao do rato
 *@return valor inteiro que diz a nova posicao do rato
 */
int mouse_outV(int aux);

/**
 * @brief verifica se o botao esquerdo rato foi clicado
 * @return inteiro 1 se o botao esquerdo foi pressionado, 0 se nao
 */
int clickedMouse();

/**
 * @brief retorna o valor na posicao bit de um byte
 * @param bit inteiro que tem a posicao do bit que se quer ter acesso
 * @param byte ao qual se quer aceder ao bit
 *@return valor inteiro com o valor
 */
unsigned int bit(int bit, unsigned long byte);

/**
 * @brief update a mouse
 *
 */
void update_mouse();

/**
 * @brief Mouse handler
 *
 *
 *@return valor de validacao
 */
int handle_mouse();

/**
 * @brief faz set dos pacotes do mouse
 *
 */
void mouse_set_package();

/**
 * @brief le os packets do mouse
 * @return valor inteiro de 0 em caso de sucesso, 1 em caso erro
 *
 */
int mouse_get_packet();

/**
 * @brief comando de escrita do mouse para o kbd
 *
 * @param command comando a ser escrito
 * @return valor de 0 se for bem sucedido, -1 em caso de erro
 */
int mouse_write_cmd_kbd(unsigned long command);

/**
 * @brief le comando do mouse
 *
 * @param apontador do comando a ser escrito
 * @return valor de 0 se for bem sucedido, -1 em caso de erro
 */
int mouse_read_cmd_kbd(unsigned long *command);

/**
 * @brief comando de escrita do mouse para o kbc
 *
 * @param command comando a ser escrito
 * @return valor de 0 se for bem sucedido, -1 em caso de erro
 */
int mouse_write_cmd_kbc(unsigned long command);

/**
 * @brief le resposta do buffer
 *
 *@return respota do buffer, -1 em caso de erro
 */
unsigned long mouse_read_resp();

/**
 * @brief escreve configuracao do rato
 *
 * @param cmd comando a ser escrito
 * @return valor de 0 se for bem sucedido, -1 em caso de erro
 */
int mouse_write_config(unsigned long cmd);

/**
 * @brief faz set do modo stream do mouse
 *
 * @return valor de 0 se for bem sucedido, -1 em caso de erro
 */
int mouse_set_stream_mode();

/**
 * @brief subscreve as interrupcoes do mouse
 *
 * @return valor de validacao
 */
int mouse_subscribe_int();

/**
 * @brief deixa de subscrever as interrupcoes do Mouse
 *
 * @return valor de validacao
 */
int mouse_unsubscribe_int();


