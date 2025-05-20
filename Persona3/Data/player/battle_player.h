#pragma once
#include "../../Common/common.h"	//상대경로 표기법
#include "../status/battle_status.h"
#include "../persona/battle_persona.h"
// 스테이터스, 페르소나, 아이템

typedef struct player {
	name playerName[8];
	PlayerStatus playerStatus;
	Persona* playerPersona;	// 페르소나 얻을 때 동적 할당
}Player;

int checkTooMuchPersona(Persona* playerPersona);	//페르소나 상한 체크
void getNewPersona(Persona* playerPersona);			//페르소나 얻을 때 공간 할당하는 함수


//나중에 aibo로 옮길 것
typedef struct aibo {
	name aiboName[8];
	int aiboIndex;
	PlayerStatus aiboStatus;
	Persona aiboPersona;
}Aibo;

