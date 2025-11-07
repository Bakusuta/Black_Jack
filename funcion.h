/*
 * funcion.h
 *
 *  Created on: 6 nov 2025
 *      Author: enigm
 */

#ifndef FUNCION_H_
#define FUNCION_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes
#define PALOS 4
#define CARAS 13
#define CARTAS 52
#define LIMITE_CARTAS 21
#define INICIALIZACION 0
#define PRIMERA_CARTA 1
#define VALIDAR_CENTINELA 1
#define FIGURA 10
#define INICIAL 1
#define AUMENTO_AS 1
#define DECREMENTO_AS 1
#define AS_UNO 10
#define AS_ONCE 11
#define CERO 0
#define LIMITE_MANO 6

// Prototipos
void Knuth_Shuffle(int deck[PALOS][CARAS]);
void deck_inicial(int deck[PALOS][CARAS]);
void ver_Mazo(int deck[PALOS][CARAS]);
void reparto(int deck[PALOS][CARAS], int *arriba, int *juego, int *ases);
void accion_Jugador(int decks[PALOS][CARAS], int *up, int *game, int *Az);
void accion_Dealer(int decks[PALOS][CARAS], int *up, int *game_Player, int *game_Dealer, int *Az);

#endif /* FUNCION_H_ */
