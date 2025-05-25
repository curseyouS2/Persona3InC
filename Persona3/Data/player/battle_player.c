#include "battle_player.h"
/*
// 플레이어 페르소나 저장 구조체
typedef struct playerPersonaList {	
	Persona playerPersona[];
	int numPersona;	//현재 페르소나 수
	int nowPersona;	//현재 장착한 페르소나 
}PersonaList;

typedef struct playerstatus {	//player.h, aibo.h 에서 사용, 세부 능력치는 페르소나에 따라 달라지므로 뺐음
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int buff[3];	//공, 방, 속
	int debuff[3];
}PlayerStatus;

// 플레이어 구조체
typedef struct player {
	name playerName[100];
	PlayerStatus playerStatus;
	PersonaList personaList;	// 페르소나 얻을 때 동적 할당
}Player;

*/
typedef struct player {
	name playerName[100];
	PlayerStatus playerStatus;
	PersonaList personaList;
}Player;

void initPlayer(Player* p)
{
	strcpy(p->playerName, "유키");
	p->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	//구조체 리터럴 생성...형변환이 아니라!!
	p->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty },  // playerPersona 배열
	1,  // numPersona
	0   // nowPersona
	};
}

int checkTooMuchPersona(Player p)
{
	return p.personaList.numPersona == 8;
}

void getNewPersona(Player p, Persona newpersona)
{
	if (checkTooMuchPersona(p))
	{
		printf("페르소나가 너무 많습니다...");
	}
	else
	{
		

	}
}


//Player Explayer = {







//}