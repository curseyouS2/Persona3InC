#pragma once
#include "../../../Common/common.h"
#include "../skills/battle_skills.h"

// 이름, 인덱스, 공, 마, 속, 내, 운, 내성, 스킬풀
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