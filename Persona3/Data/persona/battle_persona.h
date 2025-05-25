#pragma once
#include "../../Common/common.h"
#include "../skills/battle_skills.h"

// 이름, 인덱스, 공, 마, 속, 내, 운, 내성, 스킬풀
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