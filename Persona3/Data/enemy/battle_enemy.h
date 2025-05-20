#pragma once
#include "../status/battle_status.h"


typedef struct enemy 
{
	name enemyName[20];			// 적 이름
	index enemyIndex;				// 적 인덱스	
	int enemyExp;				// 적을 잡고 얻는 경험치
	int enemyDropItem[3];	// 적을 잡고 얻을 수 있는 아이템 종류

	EnemyStatus enemystatus;
}Enemy;