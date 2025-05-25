#pragma once
#include "../../Common/common.h"

// ��ų �迭
// ���� ����: ����, Ÿ��, ����
// ���� ����: ȭ��, ����, ����, ��ǳ, ��, ���, ���Ӽ�
// ȸ��:
// ���� ����:
// �����̻�

typedef struct phycialttack {
	char name[20];
	int skillIndex;
	int damage;
	double cost;		//hpMax�� ���ؼ� �� �� ����
	int type;
	int target;		//���� Ÿ�� �Ǵ� ��ü Ÿ�� 0�̸� ����, ��ü�� 1
	int accuracy;	//���� Ȯ��
	int times;		//�� �� ������ ��
}PhysicalAttack;

typedef struct magicattack {
	char name[20];
	int skillIndex;
	int damage;
	int cost;
	int type;
	int target;		//���� Ÿ�� �Ǵ� ��ü Ÿ�� 0�̸� ����, ��ü�� 1
	int accuracy;	//���� Ȯ��
	int times;		//�� �� ������ ��
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
	int	weirdtype;	//�����̻� Ÿ��...
}AbnormalStatus;

//int wholeSkill[100]