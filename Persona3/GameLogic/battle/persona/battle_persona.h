#pragma once
#include "../../../Common/common.h"
#include "../skills/battle_skills.h"

// �̸�, �ε���, ��, ��, ��, ��, ��, ����, ��ųǮ
typedef struct persona {
	char name[20];
	int personaIndex;
	int personaLevel;
	int stronger;
	int intelligence;
	int speed;
	int duration;
	int luck;
	int weekness[9];
	int skillPool[8];
}Persona;