#pragma once
#include "../status/battle_status.h"


typedef struct enemy 
{
	name enemyName[20];			// �� �̸�
	index enemyIndex;				// �� �ε���	
	int enemyExp;				// ���� ��� ��� ����ġ
	int enemyDropItem[3];	// ���� ��� ���� �� �ִ� ������ ����

	EnemyStatus enemystatus;
}Enemy;