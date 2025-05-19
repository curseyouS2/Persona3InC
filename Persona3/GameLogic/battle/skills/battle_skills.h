#pragma once
#include "../../../Common/common.h"

// ��ų �迭
// ���� ����: ����, Ÿ��, ����
// ���� ����: ȭ��, ����, ����, ��ǳ, ��, ���, ���Ӽ�
// ȸ��:
// ���� ����:
// �����̻�
#define NONE 0
#define SLASH 1
#define HIT 2
#define FIRE 3
#define ICE 4
#define ELECTRIC 5
#define WIND 6
#define LIGHT 7
#define DARK 9

typedef struct phycialttack {
	char name[20];
	int skillIndex;
	int damage;
	int times;		//�� �� ������ ��
	double cost;		//hpMax�� ���ؼ� �� �� ����
	int type;
	int target;		//���� Ÿ�� �Ǵ� ��ü Ÿ�� 0�̸� ����, ��ü�� 1
	int accuracy;	//���� Ȯ��
}PhysicalAttack;

typedef struct magicattack {
	char name[20];
	int skillIndex;
	int damage;
	int times;		//�� �� ������ ��
	int cost;
	int type;
	int target;		//���� Ÿ�� �Ǵ� ��ü Ÿ�� 0�̸� ����, ��ü�� 1
	int accuracy;	//���� Ȯ��
}MagicAttack;

typedef struct immediatedeath {
	char skillname[20];
	int skillIndex;
	int damage;
	int cost;
	int type;
	int target;		//���� Ÿ�� �Ǵ� ��ü Ÿ�� 0�̸� ����, ��ü�� 1
	int accuracy;	//���� Ȯ��
}ImmediateDeath;

typedef struct heal {
	char skillname[20];
	int skillIndex;
	int amount;
	int cost;
	int target;
}Heal;

// ���� �Ǵ� �����
// �̸�, �ε���, �ܰ�, ���, ������
typedef struct buff {	
	char skillname[20];
	int skillIndex;
	int stage;	
	int cost;
	int duration;
}Buff;

typedef Buff DeBuff;

typedef struct doublepower {	// ����, ����Ʈ����Ʈ
	char skillname[20];
	int skillIndex;
	int cost;
	int Activate;	//Ȱ��ȭ?
}DoublePower;

typedef struct abnormalstatusskill {	// ���� �̻�
	char skillname[20];
	int skillIndex;
	int cost;
	int type;	//�����̻� Ÿ��...
}AbnormalStatus;
