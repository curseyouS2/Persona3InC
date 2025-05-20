#include "battle_persona.h"
// 페르소나 목록
// 이름, 인덱스, 페르소나 레벨, 공, 마, 속, 내, 운, {내성}, {스킬풀}
/*
typedef struct persona {
	name personaName[20];
	index personaIndex;
	level personaLevel;
	int stronger;
	int intelligence;
	int speed;
	int duration;
	int luck;
	int weekness[9];
	int skillPool[8];
}Persona;
*/


Persona sample = 
{ "샘플페르소나", 0,	1,
1, 1, 1, 1, 1,					// 공, 마, 속, 내, 운
{0, 0, 0, 0, 0, 0, 0, 0 ,0},	// 참, 타, 관, 화, 빙, 전, 풍, 명, 암
{0, 0, 0, 0, 0, 0, 0, 0} };

Persona orpheus = 
{ "오르페우스", 1, 1,
2, 2, 2, 2, 2,
{0, 0, 0, 0, 0, 1, 0, 0 ,1}, 	
{1, 2, 3, 0, 0, 0, 0, 0} };