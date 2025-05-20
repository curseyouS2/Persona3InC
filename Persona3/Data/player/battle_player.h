#pragma once
#include "../../Common/common.h"	//����� ǥ���
#include "../status/battle_status.h"
#include "../persona/battle_persona.h"
// �������ͽ�, �丣�ҳ�, ������

typedef struct player {
	name playerName[8];
	PlayerStatus playerStatus;
	Persona* playerPersona;	// �丣�ҳ� ���� �� ���� �Ҵ�
}Player;

int checkTooMuchPersona(Persona* playerPersona);	//�丣�ҳ� ���� üũ
void getNewPersona(Persona* playerPersona);			//�丣�ҳ� ���� �� ���� �Ҵ��ϴ� �Լ�


//���߿� aibo�� �ű� ��
typedef struct aibo {
	name aiboName[8];
	int aiboIndex;
	PlayerStatus aiboStatus;
	Persona aiboPersona;
}Aibo;

