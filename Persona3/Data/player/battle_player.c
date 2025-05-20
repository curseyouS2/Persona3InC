#include "battle_player.h"
/*
typedef struct player {
	name playerName[8];
	PlayerStatus playerStatus;
	Persona playerPersona*;
}Player;

*/

Persona* playerPersona;

void getNewPersona(Persona* playerPersona)
{
	if (checkTooMuchPersona(playerPersona))
	{
		printf("페르소나가 너무 많습니다...");
	}
	else
	{
		playerPersona

	}
}

int checkTooMuchPersona(Persona playerPersona*)
{
	return sizeof(playerPersona) > (8 * Persona);
}

Player Explayer = {







}