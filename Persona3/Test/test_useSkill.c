#include "test_useSkill.h"

typedef enum skillType {	// 스킬 종류
	PHYSICAL, MAGIC, IMDEATH, HEAL, BUFF, DEBUFF, DOUBLEP, ABNORMAL
}SkillType;

typedef union skillTypeData {	//공용체로 구현, 스킬 별 작동 방식...
	PhysicalAttack physic;
	MagicAttack magic;
	ImmediateDeath imDeath;
	Heal heal;
	Buff buff;
	DeBuff debuff;
	DoublePower doubleP;
	AbnormalStatus abnormal;
}SkillTypeData;

typedef struct skill {	//스킬 구조체 -> 이름, 스킬 종류, 종류 별 작동 방식
	name skillname[100];
	SkillType skillType;	//enum
	SkillTypeData skillData;	//union
}Skill;

// 테스트용 스킬 구현////////////
	//물리계
	/*typedef struct phycialttack {
	double cost;
	int amount;
	int times;	 // 번 수
	int target;	 //적군, 적군 전체, 아군, 아군 전체
	int accuracy;
	int property; // 스킬 속성
	}PhysicalAttack;*/

Skill testHITskill = { "테스트타격스킬", PHYSICAL, {0.07, 10, 1, 0, 100, HIT} };

int physicDouble(Player* player)	//차지 활성화?
{
	return player->playerStatus.physicdouble;
}
int magicDouble(Player* player)	//컨센트레이트 활성화?
{
	return player->playerStatus.magicdouble;
}

int calcDamage(Skill* skill, Player* player, int amount, int stat) 
{
	int damage = amount;
	int statBonus = stat;
	damage += stat;
	if (player->playerStatus.buff[0])
	{
		int buffBonus = 0.3 * damage;
		damage += buffBonus;
	}
	if (physicDouble(player)) 
	{
		damage *= 2;
	}
	return damage;
}

void attack(Player* player, int damage, Enemy* enemy)
{
	enemy->enemystatus.hp -= damage;
}

void imDeath(Enemy* enemy)
{
	
}

void useSkill(Skill* skill, Player* player, Persona* persona)
{
	int damage = 0;
	int cost = 0;

	switch (skill->skillType) {

	case PHYSICAL:
		cost = (skill->skillData.physic.cost) * (player->playerStatus.hpMax);
		player->playerStatus.hp -= cost;
		damage = calcDamage(skill, player, skill->skillData.physic.amount, persona->stronger);
		break;
	case MAGIC:
		cost = skill->skillData.imDeath.cost;
		player->playerStatus.mp -= cost;
		//damage = calcDamage(Skill* skill, Player* player);
		//attack(Player* player, int damage, Enemy* enemy);
		break;
	case IMDEATH:
		cost = skill->skillData.imDeath.cost;
		player->playerStatus.mp -= cost;
		//attack
		break;
	case HEAL:
		cost = skill->skillData.heal.cost;
		player->playerStatus.mp -= cost;
		//heal();
		break;
	case BUFF:
		//buff(Player* player, Skill* skill)
		player->playerStatus.buff[skill->skillData.buff.bufftype] += 3;
		break;
	case DEBUFF:
		player->playerStatus.buff[skill->skillData.buff.bufftype] += 3;
	case DOUBLEP:
		break;
	case ABNORMAL:
		break;
	}

}