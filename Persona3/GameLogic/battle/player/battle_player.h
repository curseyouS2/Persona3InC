#pragma once
#include "../../../Common/common.h"	//����� ǥ���
#include "../status/battle_status.h"
#include "../persona/battle_persona.h"
// �������ͽ�, �丣�ҳ�, ������

typedef struct player {
	char name[8];
	PlayerStatus playerStatus;
	Persona playerPersona[8];
}Player;

//���߿� aibo�� �ű� ��
typedef struct aibo {
	char name[8];
	int aiboIndex;
	PlayerStatus aiboStatus;
	Persona aiboPersona;
}Aibo;

