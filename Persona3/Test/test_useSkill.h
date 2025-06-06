#pragma once
#include "../Common/common.h"
#include "../Data/data.h"

typedef struct phycialttack {
	double cost;
	int amount;
	int times;	 // 번 수
	int target;
	int accuracy;
	int property; // 스킬 속성
}PhysicalAttack;

typedef struct magicattack {
	int cost;
	int amount;
	int times;	 // 번 수
	int target;
	int accuracy;
	int property; // 스킬 속성
}MagicAttack;

typedef struct immediatedeath {
	int cost;
	int amount;
	int times;	 // 번 수
	int target;
	int accuracy;
	int property; // 스킬 속성
}ImmediateDeath;

typedef struct heal {
	int cost;
	int amount;
	int times;	 // 번 수
	int target;
	int accuracy;
	int property; // 스킬 속성
}Heal;

// 버프 또는 디버프
// 이름, 인덱스, 단계, 비용, 지속턴
typedef struct buff {
	int cost;
	int bufftype; //0, 1, 2 공, 방, 속
	int target;	  //적군, 적군 전체, 아군, 아군 전체 0, 1, 2, 3
}Buff;

typedef Buff DeBuff;

typedef struct doublepower {	// 차지, 컨센트레이트
	int Activate;	//활성화?
}DoublePower;

typedef struct abnormalstatusskill {	// 상태 이상
	int cost;
	int target;
	int accuracy;
	int	weirdtype;	//상태이상 타입...
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