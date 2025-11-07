/*
 ============================================================================
 Name        : Blakc_Jack_21.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcion.h"

//Constantes
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

//Inicialización de variables
int mazo[PALOS][CARAS] = {INICIALIZACION};
int carta_Arriba = INICIALIZACION;
int juego_Jugador = INICIALIZACION;
int juego_Dealer = INICIALIZACION;
int as_Jugador = INICIALIZACION;
int as_Dealer = INICIALIZACION;


int main(void) {
	setbuf(stdout, NULL); //permite enviar los datos inmediatamente a la consola sin esperar a que todos los valores se llene, respetando el orden de impresion y lectura
	srand(time(NULL)); //función que establece una semilla de coordenadas mediante la hora para ofrecer un numero aleatorio
	puts("Jugaremos Black Jack 21");


	//Pre-partida
	deck_inicial(mazo); //se establecen los numeros del mazo
	Knuth_Shuffle(mazo); //se barajea por metodo Knutch
	ver_Mazo(mazo); //se visualiza el mazo barajeado


	//Inicio de partida
	//Primera ronda
	printf("Tu primera carta es: ");
	reparto(mazo, &carta_Arriba, &juego_Jugador, &as_Jugador);
	printf("[%d] \n", juego_Jugador);
	printf("La Carta boca arriba del Dealer es: ");
	reparto(mazo, &carta_Arriba, &juego_Dealer, &as_Dealer);
	printf("[%d] \n", juego_Dealer);

	//Segunda ronda
	printf("Tu segunda carta es: ");
	reparto(mazo, &carta_Arriba, &juego_Jugador, &as_Jugador);
	printf("[%d] \n", juego_Jugador);


	//Acción del jugador
	accion_Jugador(mazo, &carta_Arriba, &juego_Jugador, &as_Jugador);


	//acciones Dealer
	accion_Dealer(mazo, &carta_Arriba, &juego_Jugador, &juego_Dealer, &as_Dealer);

	return INICIAL;
}
