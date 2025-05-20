#pragma once
#include "../../Common/common.h"

// 기본스테이터스 말고도 상태이상까지 다루는 헤더 파일

// 플레이어, 동료 스테이터스
typedef struct playerstatus {	//player.h, aibo.h 에서 사용, 세부 능력치는 페르소나에 따라 달라지므로 뺐음
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int buff[3];	//공, 방, 속
	int debuff[3];	
}PlayerStatus;

// 적 스테이터스 
typedef struct enemystatus {	//enemy.h에서 사용
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int stronger;
	int intelligence;
	int speed;
	int duration;
	int luck;
	int weekness[9];
	int buff[3];	//공, 방, 속
	int debuff[3];
}EnemyStatus;