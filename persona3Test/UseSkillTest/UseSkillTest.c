#include "UseSkillTest.h"

void initPlayer(Player* player) 
{
	strcpy(player->playerName, "��Ű");
	player->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	//����ü ���ͷ� ����...����ȯ�� �ƴ϶�!!
	player->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty }, 1, 0 };  // numPersona, nowpersona
}

// 2�� ����
int physicDouble(Player* player) 
{
	return player->playerStatus.physicdouble;
}
int magicDouble(Player* player) 
{
	return player->playerStatus.magicdouble;
}

// ������ ���(useSkill ���� ���ο��� ���)
int calcDamage(Skill* skill, Player* player, int amount, stat bonus)
{
	int damage = amount;
	int statBonus = bonus;
	damage += statBonus;
	if (player->playerStatus.buff[0])	//���� �ִٸ�
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

// ������ ����	... ���� Ȯ�� ���, 
void attack(int damage, Enemy* enemy)
{

}
// �� ����
void heal(Skill* skill, Player* player)	//���߿� aibo �߰��� �� �ƴϸ� aibo�� enemy�� ���� ������ ¥�°� ��������
{
	int currentHp = player->playerStatus.hp,
		healAmount = skill->skillData.heal.amount,
		maxHp = player->playerStatus.hpMax;
	currentHp += healAmount;
	if (currentHp > maxHp)	currentHp = maxHp;
}

// ���� Ȯ�� ��� 
int imDeath(Skill* skill, Player* player, Enemy* enemy) // �⺻ ���߷�, �÷��̾�/�� ȸ��-���� ���� ���)
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
	srand(time(NULL));	//�������� realChance���� ũ�� ����
	int nowChance = rand() % 100 + 1;	//1���� 100����
	if (nowChance > realChance) 
	{
		printf("���� ȸ��!\n");
		return 0;
	}
	else
	{
		printf("���� ����!\n");
		return 1;
	}
}

// ��ų ���
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

// ��ų ����
/*
	name skillname[100];
	SkillType skillType;
	SkillTypeData skillData;
*/
Skill Agi = { "�Ʊ�", , 
}


// �丣�ҳ� ����
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
	"������콺", 1,
	10, 10, 10, 10, 10,
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
}

