#pragma once
#include "../../Common/common.h"
#include "../skills/battle_skills.h"

// �̸�, �ε���, ��, ��, ��, ��, ��, ����, ��ųǮ
typedef struct persona {
	name personaName[100];
	index personaIndex;
	level personaLevel;
	stat stronger;
	stat intelligence;
	stat speed;
	stat duration;
	stat luck;
	int weekness[9];
	int skillPool[8];
}Persona;

extern const Persona empty;
extern const Persona orpheus;