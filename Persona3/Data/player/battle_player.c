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
		printf("�丣�ҳ��� �ʹ� �����ϴ�...");
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