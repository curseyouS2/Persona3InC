#pragma once
#include "../../../Common/common.h"

// �÷��̾�, ���� �������ͽ�
typedef struct playerstatus {	//player.h, aibo.h ���� ���
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int buff[3];	//��, ��, ��
	int debuff[3];	
}PlayerStatus;

// �� �������ͽ� 
typedef struct enemystatus {	//enemy.h���� ���
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
	int buff[3];	//��, ��, ��
	int debuff[3];
}EnemyStatus;