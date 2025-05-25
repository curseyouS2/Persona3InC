#pragma once
#include "../../Common/common.h"	//����� ǥ���
#include "../status/battle_status.h"
#include "../persona/battle_persona.h"
// �������ͽ�, �丣�ҳ�, ������

typedef struct playerPersonaList {	// �÷��̾� �丣�ҳ� ����
	Persona playerPersona[8];
	int numPersona;
	int nowPersona;
}PersonaList;

/*
typedef struct playerstatus {	//player.h, aibo.h ���� ���, ���� �ɷ�ġ�� �丣�ҳ��� ���� �޶����Ƿ� ����
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int buff[3];	//��, ��, ��
	int debuff[3];
}PlayerStatus;
*/

// �÷��̾� ����ü
typedef struct player {
	name playerName[100];
	PlayerStatus playerStatus;
	PersonaList personaList;	
}Player;

void initPlayer(Player* p);			//�÷��̾� �ʱ�ȭ
int checkTooMuchPersona(Player p);	//�丣�ҳ� ���� üũ
void getNewPersona(Player p, Persona newpersona);			//�丣�ҳ� ���� �� ���� �Ҵ��ϴ� �Լ�


//���߿� aibo�� �ű� ��
typedef struct aibo {
	name aiboName[8];
	int aiboIndex;
	PlayerStatus aiboStatus;
	Persona aiboPersona;
}Aibo;

