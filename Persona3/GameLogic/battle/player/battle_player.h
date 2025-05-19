#pragma once
#include "../../../Common/common.h"	//상대경로 표기법
#include "../status/battle_status.h"
#include "../persona/battle_persona.h"
// 스테이터스, 페르소나, 아이템

typedef struct player {
	char name[8];
	PlayerStatus playerStatus;
	Persona playerPersona[8];
}Player;

//나중에 aibo로 옮길 것
typedef struct aibo {
	char name[8];
	int aiboIndex;
	PlayerStatus aiboStatus;
	Persona aiboPersona;
}Aibo;

