#pragma once

/** @defgroup keyboard keyboard
 * @{
 * Functions for keyboard
 */

#define KEY_DOWN(k) (k)  /**< @brief verifica se uma tecla e pressionada  */
#define KEY_UP(k) (0x80 | k) /**< @brief verifica se uma tecla nao e pressionada */
#define MSB BIT(7) /**< @brief byte mais significativo */

/// Keys
typedef enum {
    KEY_ESC = 0x0001,
    KEY_Q = 0x0010,
    KEY_E = 0x0012,
    KEY_A = 0x001E,
    KEY_D = 0x0020,
} KEY;

/**
 * @brief subscreve as interrupcoes do teclado
 *
 * @return valor de validacao
 */
int keyboard_subscribe_int();

/**
 * @brief deixa de subscrever as interrupcoes do teclado
 *
 * @return valor de validacoa
 */
int keyboard_unsubscribe_int();

/**
 * @brief le resposta do buffer
 *
 * @preturn resposta do buffer, -1 em caso de erro
 *
 */
unsigned long keyboard_read_resp();

/**
 * @brief le resposta do buffer ao fim de alguns numero de tentativas
 *
 * @preturn resposta do buffer, -1 em caso de erro
 *
 */
int keyboard_get_resp();






