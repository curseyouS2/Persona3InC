#include "UseSkillTest.h"

void initPlayer(Player* player) 
{
	strcpy(player->playerName, "유키");
	player->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	//구조체 리터럴 생성...형변환이 아니라!!
	player->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty }, 1, 0 };  // numPersona, nowpersona
}

// 2배 판정
int physicDouble(Player* player) 
{
	return player->playerStatus.physicdouble;
}
int magicDouble(Player* player) 
{
	return player->playerStatus.magicdouble;
}

// 데미지 계산(useSkill 등의 내부에서 사용)
int calcDamage(Skill* skill, Player* player, int amount, stat bonus)
{
	int damage = amount;
	int statBonus = bonus;
	damage += statBonus;
	if (player->playerStatus.buff[0])	//공증 있다면
	{
		int buffBonus = 0.3 * damage;
		damage += buffBonus;
	}
	if ( skill->skillType==PHYSICAL && physicDouble(player))
	{
		damage *= 2;
	}
	if (skill->skillType == MAGIC && magicDouble(player))
	{
		damage *= 2;
	}
	return damage;
}

// 실제로 공격	... 명중 확률 계산, 
void attack(int damage, Enemy* enemy)
{

}
// 힐 적용
void heal(Skill* skill, Player* player)	//나중에 aibo 추가할 것 아니면 aibo랑 enemy랑 같은 구조로 짜는게 나을지도
{
	int currentHp = player->playerStatus.hp,
		healAmount = skill->skillData.heal.amount,
		maxHp = player->playerStatus.hpMax;
	currentHp += healAmount;
	if (currentHp > maxHp)	currentHp = maxHp;
}

// 즉사기 확률 계산 
int imDeath(Skill* skill, Player* player, Enemy* enemy) // 기본 명중률, 플레이어/적 회피-명중 버프 계산)
{
	int defaultChance = skill->skillData.imDeath.accuracy,
		bonus1 = 0, bonus2 = 0, bonus3 = 0;
	if (player->playerStatus.buff[2])
	{
		bonus1 = defaultChance * 0.3;
	}
	if (enemy->enemyStatus.buff[2])
	{
		bonus2 = defaultChance * 0.3;
	}
	if (enemy->enemyStatus.debuff[2])
	{
		bonus3 = defaultChance * 0.3;
	}
	int realChance = defaultChance + bonus1 - bonus2 + bonus3;
	srand(time(NULL));	//랜덤값이 realChance보다 크면 실패
	int nowChance = rand() % 100 + 1;	//1부터 100까지
	if (nowChance > realChance) 
	{
		printf("즉사기 회피!\n");
		return 0;
	}
	else
	{
		printf("즉사기 명중!\n");
		return 1;
	}
}

// 스킬 사용
void useSkill(Skill* skill, Player* player, Persona* persona, Enemy* enemy)
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
		cost = skill->skillData.magic.cost;
		player->playerStatus.mp -= cost;
		damage = calcDamage(skill, player, skill->skillData.magic.amount, persona->intelligence);
		attack(damage, enemy);
		break;
	case IMDEATH:
		cost = skill->skillData.imDeath.cost;
		player->playerStatus.mp -= cost;
		if (imDeath(skill, player, enemy))
		{
			attack(enemy->enemyStatus.hpMax, enemy);
		}
		break;
	case HEAL:
		cost = skill->skillData.heal.cost;
		player->playerStatus.mp -= cost;
		heal(skill, player);
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

// 스킬 구현
/*
	name skillname[100];
	SkillType skillType;
	SkillTypeData skillData;
*/
Skill Agi = { "아기", , 
}


// 페르소나 구현
/*
	name personaName[100];
	index personaIndex;
	level personaLevel;
	stat stronger;
	stat intelligence;
	stat speed;
	stat duration;
	stat luck;
	int weekness[9];
	Skill skillPool[8];
*/

Persona orpheus = {
	"오르페우스", 1,
	10, 10, 10, 10, 10,
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
}

