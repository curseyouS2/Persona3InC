#pragma once
#include "../Common/common.h"
#include "../Data/data.h"

typedef struct phycialttack {
	double cost;
	int amount;
	int times;	 // �� ��
	int target;
	int accuracy;
	int property; // ��ų �Ӽ�
}PhysicalAttack;

typedef struct magicattack {
	int cost;
	int amount;
	int times;	 // �� ��
	int target;
	int accuracy;
	int property; // ��ų �Ӽ�
}MagicAttack;

typedef struct immediatedeath {
	int cost;
	int amount;
	int times;	 // �� ��
	int target;
	int accuracy;
	int property; // ��ų �Ӽ�
}ImmediateDeath;

typedef struct heal {
	int cost;
	int amount;
	int times;	 // �� ��
	int target;
	int accuracy;
	int property; // ��ų �Ӽ�
}Heal;

// ���� �Ǵ� �����
// �̸�, �ε���, �ܰ�, ���, ������
typedef struct buff {
	int cost;
	int bufftype; //0, 1, 2 ��, ��, ��
	int target;	  //����, ���� ��ü, �Ʊ�, �Ʊ� ��ü 0, 1, 2, 3
}Buff;

typedef Buff DeBuff;

typedef struct doublepower {	// ����, ����Ʈ����Ʈ
	int Activate;	//Ȱ��ȭ?
}DoublePower;

typedef struct abnormalstatusskill {	// ���� �̻�
	int cost;
	int target;
	int accuracy;
	int	weirdtype;	//�����̻� Ÿ��...
}AbnormalStatus;


/*typedef union skillType {
	PhysicalAttack physic;
	MagicAttack magic;
	ImmediateDeath imDeath;
	Heal heal;
	Buff buff;
	DeBuff debuff;
	DoublePower doubleP;
	AbnormalStatus abnormal;
}SkillType;*/

typedef enum skillType {
	PHYSICAL, MAGIC, IMDEATH, HEAL, BUFF, DEBUFF, DOUBLEP, ABNORMAL
}SkillType;

typedef union skillData {
	PhysicalAttack physic;
	MagicAttack magic;
	ImmediateDeath imDeath;
	Heal heal;
	Buff buff;
	DeBuff debuff;
	DoublePower doubleP;
	AbnormalStatus abnormal;
}SkillData;

typedef struct skill {
	name skillname[100];
	SkillType skillType;
	SkillData skillData;
}Skill;
int physicDouble(Player* player);
int magicDouble(Player* player);
int calcDamage(Skill* skill, Player* player, int amount);
void attack(Player* player, int damage, Enemy* enemy);
void useSkill(Skill* skill, Player* player, Persona* persona);