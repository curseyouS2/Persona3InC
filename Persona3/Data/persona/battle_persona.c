#include "battle_persona.h"
// �丣�ҳ� ���
// �̸�, �ε���, �丣�ҳ� ����, ��, ��, ��, ��, ��, {����}, {��ųǮ}
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
{ "�����丣�ҳ�", 0,	1,
1, 1, 1, 1, 1,					// ��, ��, ��, ��, ��
{0, 0, 0, 0, 0, 0, 0, 0 ,0},	// ��, Ÿ, ��, ȭ, ��, ��, ǳ, ��, ��
{0, 0, 0, 0, 0, 0, 0, 0} };

Persona orpheus = 
{ "������콺", 1, 1,
2, 2, 2, 2, 2,
{0, 0, 0, 0, 0, 1, 0, 0 ,1}, 	
{1, 2, 3, 0, 0, 0, 0, 0} };