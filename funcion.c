/*
 * funcion.c
 *
 *  Created on: 6 nov 2025
 *      Author: enigm
 */

#include "funcion.h"

//constantes
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

const char *palo[PALOS] = {"corazones", "diamantes", "treboles", "picas"};
const char *cara[CARAS] = {"As", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho", "Nueve", "Diez", "Joto", "Reina", "Rey"};

void Knuth_Shuffle(int deck[PALOS][CARAS]){ //función de barajear mediante el metodo de intercambio de knutch
	for(size_t conteo = INICIALIZACION; conteo < CARTAS - PRIMERA_CARTA; ++conteo){ //conteo para cambiar todas las cartas

		//selección de la primera carta que se intercambiara
		int fila1 = conteo / CARAS;
		int columna1 = conteo % CARAS;

		//selección de la segunda carta que se intercambiara
		int limite = rand() % (CARTAS);
		int fila2 = limite / CARAS;
		int columna2 = limite % CARAS;

		//proceso de intercambio entre la primera carta y segunda carta
		int temporal = deck[fila1][columna1];
		deck[fila1][columna1] = deck[fila2][columna2];
		deck[fila2][columna2] = temporal;
	}
}

void deck_inicial(int deck[PALOS][CARAS]){ //función establecer los numeros de cada variable del mazo del 1 al 52
	int numero = INICIAL;
	for(int conteoY = INICIALIZACION; conteoY < PALOS; ++conteoY){ //avanza primero en columna y luego en fila
		for(int conteoX = INICIALIZACION; conteoX < CARAS; ++conteoX){
			deck[conteoY][conteoX] = numero++;
		}
	}
}

void ver_Mazo(int deck[PALOS][CARAS]){ //imprime el mazo ya barajeado por solicitud de la actividad y para confirmar que el barajeo este correcto
	for (int conteoY = INICIALIZACION; conteoY < PALOS; ++conteoY) { //avanza de la misma manera que el deck inicial llendo de columna en columna y fila en fila
		for (int conteoX = INICIALIZACION; conteoX < CARAS; ++conteoX) {
			printf("%2d ", deck[conteoY][conteoX]);
		}
		printf("\n");
	}
	printf("\n");
}

void reparto(int deck[PALOS][CARAS], int *arriba, int *juego, int *ases){ //reparte la carta de más arriba del mazo al jugador que se le designe
	int limite = deck[INICIALIZACION][*arriba] - PRIMERA_CARTA; //busca el valor de la primera carta del mazo que no haya salido
	printf("%s de %s ", cara[limite % CARAS], palo[limite / CARAS]); //muestra al jugador la carta que salio
	*arriba += PRIMERA_CARTA; //aumenta el limite para decir que hay nueva carta arriba
	int valor = limite % CARAS; //calcula valor

	if(valor >= FIGURA){ //verifica si salio joto, reina o rey
		*juego += FIGURA;
	}
	else if(CERO == valor && *juego < AS_ONCE){ //verifica que sea As
		*juego += AS_ONCE;
		*ases += AUMENTO_AS; //aumenta la cantidad de ases obtenidas
	} else { //verifica que sea del 2 al 10 o si as debe valer 1
		*juego += valor + PRIMERA_CARTA;
	}

	if(*juego > LIMITE_CARTAS && *ases > CERO){ //verifica si se necesita que As sea 1 en vez de 11
			*juego -= AS_UNO; //se le resta 10 para que valga 1
			*ases -= DECREMENTO_AS;
	}
}

void accion_Jugador(int decks[PALOS][CARAS], int *up, int *game, int *Az){ //la estructura del juego del jugador
	int centinela = INICIALIZACION;
	char solicitud = ' ';
	while(centinela != VALIDAR_CENTINELA){ //ciclo while que verificara si se llega a 21, se quedo el jugador o si se excedio de cartas o puntos
		printf("cartas jugadas: %d \n", *up);
		if(*game > LIMITE_CARTAS){ //verifica si el jugador supero su limite de 21 cartas en juego
			puts("Superaste el limite de cartas");
			centinela = VALIDAR_CENTINELA;
		}
		else if(*game < LIMITE_CARTAS){ //verifica que el jugador todavia pueda decidir jugar o quedarse
			printf("Quieres jugar otra carta? \nHit (h) para agarrar otra\nStand (s) para quedarse con las cartas que se tiene \n");
			scanf(" %c", &solicitud);
			printf("%c \n", solicitud);
			if('h' == solicitud || 'H' == solicitud){//verifica si el jugador quiere agarrar otra carta
				printf("Sacas otra carta: ");
				reparto(decks, up, game, Az);
				printf("[%d] \n", *game);
				if(LIMITE_MANO == *up){ //verifica que si ya agarro 5 cartas ya no pueda jugar y se quede
					puts("Ya jugaste 5 cartas");
					centinela = VALIDAR_CENTINELA;
				}
			}
			else if('s' == solicitud || 'S' == solicitud){ //verifica si el jugador se quiere quedar con su juego
				puts("Decidiste no agarrar más cartas");
				centinela = VALIDAR_CENTINELA;
			}
		} else { //verifica si el jugador ya llego a 21
			puts("Tienes 21, ahora me toca a mi el Dealer");
			centinela = VALIDAR_CENTINELA;
		}
	}
}

void accion_Dealer(int decks[PALOS][CARAS],int *up, int *Jugador, int *Dealer, int *Az){//la logica del Dealer para abatir al jugador
	int centinela = INICIALIZACION;
	printf("La Carta boca abajo del Dealer es: "); //revela la segunda carta del jugador
	reparto(decks, up, Dealer, Az);
	printf("[%d] \n", *Dealer);
	while(centinela != VALIDAR_CENTINELA){ //ciclo que verifica si el Dealer perdio, gano o empato
		if(*Jugador > LIMITE_CARTAS){ //verifica si el jugador se excedio de puntos
			centinela = VALIDAR_CENTINELA;
			puts("perdiste");
		} else {
			if(*Dealer > LIMITE_CARTAS){ //verifica si el Dealer se excedio de puntos
				puts("felicidades, me ganaste");
				centinela = VALIDAR_CENTINELA;
			}
			else if(*Dealer <= *Jugador && *Dealer != LIMITE_CARTAS){ //verifica si el jugador todavia le gana por puntos al dealer y si aun no han llegado a 21
				puts("Jugare otra carta");
				printf("La Carta del Dealer es: ");
				reparto(decks, up, Dealer, Az);
				printf("[%d] \n", *Dealer);
			}
			else if(*Dealer > *Jugador){ //verifica si el dealer le gano al jugador
				puts("Gane como Dealer, perdiste");
				centinela = VALIDAR_CENTINELA;
			} else { //verifica si ambos quedaron empate en 21
				puts("Fue un empate");
				centinela = VALIDAR_CENTINELA;
			}
		}
	}
}
