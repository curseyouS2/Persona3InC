#pragma once
#include "../../Common/common.h"	//상대경로 표기법
#include "../status/battle_status.h"
#include "../persona/battle_persona.h"
// 스테이터스, 페르소나, 아이템

typedef struct playerPersonaList {	// 플레이어 페르소나 저장
	Persona playerPersona[8];
	int numPersona;
	int nowPersona;
}PersonaList;

/*
typedef struct playerstatus {	//player.h, aibo.h 에서 사용, 세부 능력치는 페르소나에 따라 달라지므로 뺐음
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int buff[3];	//공, 방, 속
	int debuff[3];
}PlayerStatus;
*/

// 플레이어 구조체
typedef struct player {
	name playerName[100];
	PlayerStatus playerStatus;
	PersonaList personaList;	
}Player;

void initPlayer(Player* p);			//플레이어 초기화
int checkTooMuchPersona(Player p);	//페르소나 상한 체크
void getNewPersona(Player p, Persona newpersona);			//페르소나 얻을 때 공간 할당하는 함수


//나중에 aibo로 옮길 것
typedef struct aibo {
	name aiboName[8];
	int aiboIndex;
	PlayerStatus aiboStatus;
	Persona aiboPersona;
}Aibo;

