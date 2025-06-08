#include "game.h"


// ����, ���� üũ �Լ� (calcDamage�� ��������)
int checkAttackWeakness(int isPlayer, Player* player, Persona* persona, Enemy* enemy, int damage)
{
	if (isPlayer)
	{
		int property = player->equipment.weapon.property;
		if (enemy->enemyStatus.weekness[property] != 0)
		{
			switch (enemy->enemyStatus.weekness[property])
			{
			case 1:	// ����
				printf("%s�� ������ �����ߴ�!\n", enemy->enemyName);
				return damage * 1.5;
			case 2: // �氨
				printf("%s���� �������� �ݰ��Ǿ���...\n", enemy->enemyName);
				return damage * 0.5;
			case 3: // ��ȿ
				printf("%s���Դ� ������ �ʴ´�...\n", enemy->enemyName);
				return 0;
			case 4: // �ݻ�
				player->playerStatus.hp -= damage;
				isPlayerDead(player);
				printf("%s�� ������ �ݻ��ߴ�!\n", enemy->enemyName);
				return 0;
			case 5: // ���
				enemy->enemyStatus.hp = +damage;
				if (enemy->enemyStatus.hp > enemy->enemyStatus.hpMax) enemy->enemyStatus.hp = enemy->enemyStatus.hpMax;
				printf("%s�� ������ ����ߴ�...\n", enemy->enemyName);
				return 0;
			}
		}
		return damage;
	}
	else
	{
		if (persona->weekness[0] != 0)
		{
			switch (persona->weekness[0])
			{
			case 1:	// ����
				printf("%s�� ������ �����ߴ�!\n", player->playerName);
				return damage * 1.5;
			case 2: // �氨
				printf("%s���� �������� �ݰ��Ǿ���...\n", player->playerName);
				return damage * 0.5;
			case 3: // ��ȿ
				printf("%s���Դ� ������ �ʴ´�...\n", player->playerName);
				return 0;
			case 4: // �ݻ�
				player->playerStatus.hp -= damage;
				isPlayerDead(player);
				printf("%s�� ������ �ݻ��ߴ�!\n", player->playerName);
				return 0;
			case 5: // ���
				player->playerStatus.hp = +damage;
				if (player->playerStatus.hp > player->playerStatus.hpMax) player->playerStatus.hp = player->playerStatus.hpMax;
				printf("%s�� ������ ����ߴ�...\n", player->playerName);
				return 0;
			}
		}
		return damage;
	}
}
int checkSkillWeakness(Skill* skill, int isPlayer, Player* player, Persona* persona, Enemy* enemy, int damage)
{
	int property;
	if (skill->skillType == PHYSICAL) property = skill->skillData.physic.property;
	else if (skill->skillType == MAGIC) property = skill->skillData.magic.property;
	else return damage;

	if (isPlayer)
	{
		if (enemy->enemyStatus.weekness[property] != 0)
		{
			switch (enemy->enemyStatus.weekness[property])
			{
			case 1:	// ����
				printf("%s�� ������ �����ߴ�!\n", enemy->enemyName);
				return damage * 1.5;
			case 2: // �氨
				printf("%s���� �������� �ݰ��Ǿ���...\n", enemy->enemyName);
				return damage * 0.5;
			case 3: // ��ȿ
				printf("%s���Դ� ������ �ʴ´�...\n", enemy->enemyName);
				return 0;
			case 4: // �ݻ�
				player->playerStatus.hp -= damage;
				isPlayerDead(player);
				printf("%s�� ������ �ݻ��ߴ�!\n", enemy->enemyName);
				return 0;
			case 5: // ���
				enemy->enemyStatus.hp = +damage;
				if (enemy->enemyStatus.hp > enemy->enemyStatus.hpMax) enemy->enemyStatus.hp = enemy->enemyStatus.hpMax;
				printf("%s�� ������ ����ߴ�...\n", enemy->enemyName);
				return 0;
			}
		}
	}
	else // ���� ���
	{
		if (persona->weekness[0] != 0)
		{
			switch (persona->weekness[0])
			{
			case 1:	// ����
				printf("%s�� ������ �����ߴ�!\n", player->playerName);
				return damage * 1.5;
			case 2: // �氨
				printf("%s���� �������� �ݰ��Ǿ���...\n", player->playerName);
				return damage * 0.5;
			case 3: // ��ȿ
				printf("%s���Դ� ������ �ʴ´�...\n", player->playerName);
				return 0;
			case 4: // �ݻ�
				player->playerStatus.hp -= damage;
				isPlayerDead(player);
				printf("%s�� ������ �ݻ��ߴ�!\n", player->playerName);
				return 0;
			case 5: // ���
				player->playerStatus.hp = +damage;
				if (player->playerStatus.hp > player->playerStatus.hpMax) player->playerStatus.hp = player->playerStatus.hpMax;
				printf("%s�� ������ ����ߴ�...\n", player->playerName);
				return 0;
			}
		}
	}
}
// ȸ�� �Լ� (imDeath�� ����ϰ� ���� �ɵ��ϴ�...��� ���: ����, �ӵ�����...attack ���ο� ��������)

#pragma region EQUIP
const Weapon normalSword = { "����� ��", 15, SLASH, 98 };
const Armor normalArmor = { "����� ����", 30 };

// ��� ��ü �Լ� �����ߵ�
#pragma endregion

int calcAttackDamage(int isPlayer, Player* player, Enemy* enemy)
{
	if (isPlayer)
	{
		int damage = player->equipment.weapon.power;
		return checkAttackWeakness(1, player, &player->personaList.playerPersona[player->personaList.nowPersona], enemy, damage);
	}
	else
	{
		int damage = enemy->enemyStatus.stronger;
		return checkAttackWeakness(0, player, &player->personaList.playerPersona[player->personaList.nowPersona], enemy, damage);
	}
}

#pragma region SKILL

int physicDouble(void* attacker, int isPlayer)
{
	if (isPlayer) //�÷��̾� ��
	{
		Player* player = (Player*)attacker;
		if (player->playerStatus.physicdouble)
		{
			player->playerStatus.physicdouble = 0;
			return 1;
		}
		else return 0;
	}
	else // �� ��
	{
		Enemy* enemy = (Enemy*)attacker;
		if (enemy->enemyStatus.physicdouble)
		{
			enemy->enemyStatus.physicdouble = 0;
			return 1;
		}
		else return 0;
	}
}
int magicDouble(void* attacker, int isPlayer)
{
	if (isPlayer)	//�÷��̾� ��
	{
		Player* player = (Player*)attacker;
		if (player->playerStatus.magicdouble)
		{
			player->playerStatus.magicdouble = 0;
			return 1;
		}
		else return 0;
	}
	else // �� �� 
	{
		Enemy* enemy = (Enemy*)attacker;
		if (enemy->enemyStatus.magicdouble)
		{
			enemy->enemyStatus.magicdouble = 0;
			return 1;
		}
		else return 0;
	}
}

// ��ų ������ ���
int calcSkillDamage(const Skill* skill, void* attacker, int isPlayer, int amount, int statBonus)
{
	int damage = amount;
	damage += statBonus;

	int isAttackBuff = 0;
	int isAttackDebuff = 0;
	int isDefenseBuff = 0;
	int isDefenseDeBuff = 0;
	int isPhysicdouble = 0;
	int isMagicdouble = 0;

	// ���� ��ü�� ���� �ʱ� ����
	if (isPlayer)
	{
		Player* player = (Player*)attacker;
		isAttackBuff = player->playerStatus.buff[0];
		isAttackDebuff = player->playerStatus.debuff[0];
		isPhysicdouble = physicDouble(attacker, isPlayer);
		isMagicdouble = magicDouble(attacker, isPlayer);
	}
	else
	{
		Enemy* enemy = (Enemy*)attacker;
		isAttackBuff = enemy->enemyStatus.buff[0];
		isAttackDebuff = enemy->enemyStatus.debuff[0];
		isPhysicdouble = physicDouble(attacker, isPlayer);
		isMagicdouble = magicDouble(attacker, isPlayer);
	}

	if (isAttackBuff || isAttackDebuff)	//���ݷ� ��������� �ִٸ�
	{
		int attackBuffBonus = 0.3 * damage;
		int attackDebuffBonus = 0.3 * damage;
		if (isAttackBuff) damage += attackBuffBonus;
		if (isAttackDebuff) damage -= attackDebuffBonus;
	}
	// 2�� ���� ���� ��������
	if (skill->skillType == PHYSICAL && isPhysicdouble) damage *= 2;
	if (skill->skillType == MAGIC && isMagicdouble) damage *= 2;

	return damage;
}

// ������ ����	... ���� Ȯ�� ���, 
void attack(int damage, Enemy* enemy)
{
	enemy->enemyStatus.hp -= damage;
	Sleep(1000);
}
void attackPlayer(int damage, Player* player)
{
	player->playerStatus.hp -= damage;
}
// �� ����
void heal(Skill* skill, Player* player)	//���߿� aibo �߰��� �� �ƴϸ� aibo�� enemy�� ���� ������ ¥�°� ��������
{
	int currentHp = player->playerStatus.hp,
		healAmount = skill->skillData.heal.amount,
		maxHp = player->playerStatus.hpMax;
	currentHp += healAmount;
	if (currentHp > maxHp)	currentHp = maxHp;
	printf("\n%d��ŭ ȸ����\n", healAmount);
	player->playerStatus.hp = currentHp;
}
void healEnemy(Skill* skill, Enemy* enemy)	//���߿� aibo �߰��� �� �ƴϸ� aibo�� enemy�� ���� ������ ¥�°� ��������
{
	int currentHp = enemy->enemyStatus.hp,
		healAmount = skill->skillData.heal.amount,
		maxHp = enemy->enemyStatus.hpMax;
	currentHp += healAmount;
	if (currentHp > maxHp)	currentHp = maxHp;
	printf("\n%s�� %d��ŭ ȸ����\n", enemy->enemyName, healAmount);
	enemy->enemyStatus.hp = currentHp;
}

// ���� Ȯ�� ��� 
int imDeath(const Skill* skill, void* attacker, int isPlayer, Player* player, Enemy* enemy)
{
	int defaultChance = skill->skillData.imDeath.accuracy;
	int bonus1 = 0, bonus2 = 0, bonus3 = 0, bonus4 = 0;

	if (isPlayer)
	{
		Player* attackerPlayer = (Player*)attacker;

		if (player->playerStatus.buff[2])	bonus1 = defaultChance * 0.3;
		if (player->playerStatus.debuff[2])	bonus2 = defaultChance * 0.3;
		if (enemy->enemyStatus.buff[2])		bonus3 = defaultChance * 0.3;
		if (enemy->enemyStatus.debuff[2])	bonus4 = defaultChance * 0.3;
	}
	else
	{
		Enemy* attackerEnemy = (Enemy*)attacker;
		if (enemy->enemyStatus.buff[2])		bonus1 = defaultChance * 0.3;
		if (enemy->enemyStatus.debuff[2])	bonus2 = defaultChance * 0.3;
		if (player->playerStatus.buff[2])	bonus3 = defaultChance * 0.3;
		if (player->playerStatus.debuff[2])	bonus4 = defaultChance * 0.3;
	}

	int realChance = defaultChance - bonus1 + bonus2 + bonus3 - bonus4;

	// �������� realChance���� ũ�� ����...realChance�� Ŭ���� �±� ��ư���?
	int nowChance = rand() % 100 + 1;    // 1���� 100����

	if (nowChance > realChance)
	{
		return 0;    // ����
	}
	else
	{
		return 1;    // ����
	}
}

// ��ų ���

void useSkill(const Skill* skill, void* attacker, int isPlayer, Player* player, NowEnemy* currentEnemyGroup)
{
	int damage = 0;
	int cost = 0;
	int statBonus = 0;

	Player* attackerPlayer = NULL;
	Enemy* attackerEnemy = NULL;
	Persona* currentPersona = NULL;
	#pragma region SETUP
	if (isPlayer)
	{
		attackerPlayer = (Player*)attacker;
		currentPersona = &attackerPlayer->personaList.playerPersona[attackerPlayer->personaList.nowPersona];

		if (skill->skillType == PHYSICAL)
		{
			statBonus = currentPersona->stronger;
		}
		else if (skill->skillType == MAGIC)
		{
			statBonus = currentPersona->intelligence;
		}
	}
	else
	{
		attackerEnemy = (Enemy*)attacker;

		if (skill->skillType == PHYSICAL)
		{
			statBonus = attackerEnemy->enemyStatus.stronger;
		}
		else if (skill->skillType == MAGIC)
		{
			statBonus = attackerEnemy->enemyStatus.intelligence;
		}
	}
#pragma endregion
	switch (skill->skillType)
	{
	#pragma region PHYSICAL
	case PHYSICAL:
		if (isPlayer)
		{
			cost = (skill->skillData.physic.cost) * (attackerPlayer->playerStatus.hpMax);
			attackerPlayer->playerStatus.hp -= cost;
			damage = calcSkillDamage(skill, attacker, isPlayer, skill->skillData.physic.amount, statBonus);

			if (skill->skillData.physic.target == 0)
			{
				int choose = selectTarget(currentEnemyGroup);
				Enemy* e = &currentEnemyGroup->enemyGroup[choose];
				printf("%s ���!\n", skill->skillName);
				attack(damage, e);
				printf("%s���� %d��ŭ�� �������� �������ϴ�...\n", e->enemyName, damage);
				if (isEnemyDead(*e))
				{
					setEnemyIndex(currentEnemyGroup);
				}
			}
		}
		else
		{
			cost = (skill->skillData.physic.cost) * (attackerEnemy->enemyStatus.hpMax);
			attackerEnemy->enemyStatus.hp -= cost;

			damage = calcSkillDamage(skill, attacker, isPlayer, skill->skillData.physic.amount, statBonus);

			printf("%s ���!\n", skill->skillName);
			attackPlayer(damage, player); // ���⼭ player �Ű����� ��� (�ʼ�!)
			printf("�÷��̾�� %d��ŭ�� �������� �������ϴ�...\n", damage);
		}
		break;
#pragma endregion

	#pragma region MAGIC
		case MAGIC:
		if (isPlayer)
		{
			cost = skill->skillData.magic.cost;
			attackerPlayer->playerStatus.mp -= cost;

			damage = calcSkillDamage(skill, attacker, isPlayer, skill->skillData.magic.amount, statBonus);

			if (skill->skillData.magic.target == 0)
			{
				int choose = selectTarget(currentEnemyGroup);
				Enemy* e = &currentEnemyGroup->enemyGroup[choose];
				printf("%s ���!\n", skill->skillName);
				attack(damage, e);
				printf("%s���� %d��ŭ�� �������� �������ϴ�...\n", e->enemyName, damage);
				if (isEnemyDead(*e))
				{
					setEnemyIndex(currentEnemyGroup);
				}
			}
		}
		else
		{
			cost = skill->skillData.magic.cost;
			attackerEnemy->enemyStatus.mp -= cost;

			damage = calcSkillDamage(skill, attacker, isPlayer, skill->skillData.magic.amount, statBonus);

			printf("%s ���!\n", skill->skillName);
			attackPlayer(damage, player);
			printf("�÷��̾�� %d��ŭ�� �������� �������ϴ�...\n", damage);
		}
		break;
#pragma endregion

	#pragma region IMDEATH
	case IMDEATH:
		cost = skill->skillData.imDeath.cost;

		if (isPlayer)
		{
			attackerPlayer->playerStatus.mp -= cost;

			if (skill->skillData.imDeath.target == 0)
			{
				int choose = selectTarget(currentEnemyGroup);
				Enemy* e = &currentEnemyGroup->enemyGroup[choose];
				printf("%s ���!\n", skill->skillName);

				if (imDeath(skill, attacker, isPlayer, player, e))	// Ȯ������Լ�
				{
					attack(e->enemyStatus.hpMax, e);
					printf("%s ����!\n", skill->skillName);
					if (isEnemyDead(*e))
					{
						setEnemyIndex(currentEnemyGroup);	//�� ������ �� �׷� �ε��� ����
					}
				}
				else
				{
					printf("%s ������!\n", skill->skillName);
				}
			}
		}
		else // ���� ����
		{
			attackerEnemy->enemyStatus.mp -= cost;

			printf("%s ���!\n", skill->skillName);
			if (imDeath(skill, attacker, isPlayer, player, NULL))	// Ȯ������Լ�
			{
				attackPlayer(player->playerStatus.hpMax, player);
				printf("%s ����!\n", skill->skillName);
				if (isPlayerDead(player))
				{
					printf("���ӿ���...\n");
				}
			}
			else
			{
				printf("%s ������!\n", skill->skillName);
			}
		}
		break;
#pragma endregion

	#pragma region HEAL
		case HEAL:
			cost = skill->skillData.heal.cost;
			if (isPlayer)
			{
				attackerPlayer->playerStatus.mp -= cost;
				heal(skill, attackerPlayer);
			}
			else
			{
				attackerEnemy->enemyStatus.mp -= cost;
				healEnemy(skill, attackerEnemy);
			}
			break;
	#pragma endregion

	#pragma region BUFF
		case BUFF:
			if (isPlayer)
			{
				attackerPlayer->playerStatus.mp -= skill->skillData.buff.cost;
				if (skill->skillData.buff.target == 0)
				{
					printf("%s ���!\n", skill->skillName);
					attackerPlayer->playerStatus.buff[skill->skillData.buff.bufftype] = 3;
				}
			}
			else // ���� ���� ��� ��
			{
				attackerEnemy->enemyStatus.mp -= skill->skillData.buff.cost;
				if (skill->skillData.buff.target == 0)
				{
					attackerEnemy->enemyStatus.buff[skill->skillData.buff.bufftype] = 3;
				}
			}
			break;
	#pragma endregion

	#pragma region DEBUFF
	case DEBUFF:
		if (isPlayer)
		{
			if (skill->skillData.debuff.target == 0)
			{
				int choose = selectTarget(currentEnemyGroup);
				Enemy* e = &currentEnemyGroup->enemyGroup[choose];
				printf("%s ���!\n", skill->skillName);

				attackerPlayer->playerStatus.mp -= skill->skillData.debuff.cost;
				if (skill->skillData.debuff.target == 0)
				{
					e->enemyStatus.debuff[skill->skillData.debuff.bufftype] = 3;
				}

			}

		}
		else // ���� ���� ��� ��
		{
			attackerEnemy->enemyStatus.mp -= skill->skillData.debuff.cost;
			if (skill->skillData.debuff.target == 0)
			{
				printf("%s�� %s ���!\n", attackerEnemy->enemyName, skill->skillName);
				player->playerStatus.debuff[skill->skillData.debuff.bufftype] = 3;
			}
		}
		break;
#pragma endregion

	#pragma region DOUBLEP
	case DOUBLEP:
		if (isPlayer) //�÷��̾� ��
		{
			if (skill->skillData.doubleP.type == 0) //����
			{
				if (attackerPlayer->playerStatus.physicdouble == 0)
				{
					attackerPlayer->playerStatus.physicdouble = 1;
					printf("%s ���! \n", skill->skillName);
					printf("%s�� ������ ����ϴ� ���� ��ų�� ������ 2�谡 �ȴ�...\n", attackerPlayer->playerName);
				}
				else
				{
					printf("%s�� �̹� ����Ǿ��ִ�!\n", skill->skillName);
				}
			}

			if (skill->skillData.doubleP.type == 1) // ����Ʈ����Ʈ
			{
				if (attackerPlayer->playerStatus.magicdouble == 0)
				{
					attackerPlayer->playerStatus.magicdouble = 1;
					printf("%s ���! \n", skill->skillName);
					printf("%s�� ������ ����ϴ� ���� ��ų�� ������ 2�谡 �ȴ�...\n", attackerPlayer->playerName);
				}
				else
				{
					printf("%s�� �̹� ����Ǿ��ִ�!\n", skill->skillName);
				}
			}
		}
		else // �� ��
		{
			if (skill->skillData.doubleP.type == 0) //����
			{
				if (attackerEnemy->enemyStatus.physicdouble == 0)
				{
					attackerEnemy->enemyStatus.physicdouble = 1;
					printf("%s ���! \n", skill->skillName);
					printf("%s�� ������ ����ϴ� ���� ��ų�� ������ 2�谡 �ȴ�...\n", attackerEnemy->enemyName);
				}
				else
				{
					printf("%s�� �̹� ����Ǿ��ִ�!\n", skill->skillName);
				}
			}

			if (skill->skillData.doubleP.type == 1) //����Ʈ����Ʈ
			{
				if (attackerEnemy->enemyStatus.physicdouble == 0)
				{
					attackerEnemy->enemyStatus.magicdouble = 1;
					printf("%s ���! \n", skill->skillName);
					printf("%s�� ������ ����ϴ� ���� ��ų�� ������ 2�谡 �ȴ�...\n", attackerEnemy->enemyName);
				}
				else
				{
					printf("%s�� �̹� ����Ǿ��ִ�!\n", skill->skillName);
				}
			}
		}
		break;
#pragma endregion

	case ABNORMAL: // ���߿� ����...
		break;
	}

}

// ��ų ����
	#pragma region SkillDescription
/*
	name skillname[100];
	SkillType skillType;
	SkillTypeData skillData;
*/
const Skill Noskill = { "�� ����", NOSKILL, {.physic = {0, 0, 0, 0, 0, SLASH}} };

const Skill Slash = { "������", PHYSICAL, {.physic = {0.07, 50, 1, 0, 100, SLASH}} };
const Skill Agi = { "�Ʊ�", MAGIC, {.magic = {10, 50, 1, 0, 50, FIRE}} };
const Skill Bufu = { "����", MAGIC, {.magic = {10, 50, 1, 0, 50, ICE}} };
const Skill Zio = { "����", MAGIC, {.magic = {10, 50, 1, 0, 50, ELECTRIC}} };
const Skill Garu = { "��", MAGIC, {.magic = {10, 50, 1, 0, 50, WIND}} };
const Skill Megido = { "����׽�ų", MAGIC, {.magic = {50, 200, 1, 0, 90, NONE}} };

const Skill Hama = { "�ϸ�", IMDEATH, {.imDeath = {20, 0, 80, LIGHT}} };

const Skill Dia = { "���", HEAL, {.heal = {20, 50, 1,}} };
#pragma endregion

#pragma endregion

#pragma region PERSONA
// �丣�ҳ� ����
#pragma region PersonaDescription
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

Persona empty = {
	"�� ����", 0, 00,
	0, 0, 0, 0, 0,
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{&Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill}
};
Persona orpheus = {
	"������콺", 1, 10,
	2, 2, 2, 2, 2,
	{0, 0, 0, 0, 0, WEAK, 0, 0, WEAK},
	{&Slash, &Agi, &Bufu, &Zio, &Garu, &Megido, &Hama, &Dia}
};
#pragma endregion
#pragma endregion

#pragma region PLAYER
void initPlayer(Player* player)
{
	strcpy(player->playerName, "��Ű");
	player->playerStatus = (PlayerStatus){ 500, 500, 500, 500, {0,0,0}, {0,0,0} };
	player->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty }, 1, 0 };  // numPersona, nowpersona
	player->equipment = (Equip){ normalSword, normalArmor };
}
#pragma endregion

#pragma region ENEMY

NowEnemy makeEnemy() {
	NowEnemy newEnemyGroup;
	newEnemyGroup.enemyNum = rand() % 5 + 1;
	for (int i = 0; i < newEnemyGroup.enemyNum; i++)	// allEnemy�迭
	{
		newEnemyGroup.enemyGroup[i] = *allEnemy[rand() % ALL_ENEMY];
	}
	return newEnemyGroup;
}

// �� ����
#pragma region EnemyDescription
/*
EnemyStatus
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	stat stronger;
	stat intelligence;
	stat speed;
	stat duration;
	stat luck;
	int weekness[9];
	int buff[3];	//��, ��, ��
	int debuff[3];
Enemy
	char enemyName[100];			// �� �̸�
	index enemyIndex;			// �� �ε���
	EnemyStatus enemyStatus;
	int enemyExp;				// ȹ�� ����ġ
	int enemyDropItem[3];		// ��� ������

*/

Enemy testEnemy = {
	"�׽�Ʈ�� ��", 0,
	{100, 100, 100, 100, 10, 10, 10, 10, 10,
	{0,0,0,0,0,0,0,0,0},{0,0,0}, {0,0,0}, 0, 0},
	{&Slash, &Agi, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	25, {0, 0, 1}
};
Enemy shadowSlime = {
	"������ ������", 1,
	{80, 80, 80, 80, 8, 5, 1, 5, 5,
	{0,0,0,0,0,0,0,WEAK,0}, {0,0,0}, {0,0,0}, 0, 0},
	{&Slash, &Bufu, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	15, {0, 1, 2}
};
Enemy shadowGoblin = {
	"������ ���", 2,
	{120, 50, 120, 50, 12, 1, 10, 8, 6,
	{WEAK,0,0,1,2,3,4,0,0}, {0,0,0}, {0,0,0}, 0, 0},
	{&Zio, &Slash, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	30, {1, 2, 3}
};
Enemy shadowKnight = {
	"������ ����Ʈ", 3,
	{200, 100, 200, 100, 20, 15, 12, 10, 10,
	{0,0,0,0,WEAK,0,0,0,0}, {0,0,0}, {0,0,0}, 0, 0},
	{&Slash, &Garu, &Bufu, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	50, {2, 3, 4}
};


// ��ü �� ���� �迭
Enemy* allEnemy[ALL_ENEMY] = {
	&testEnemy,
	&shadowSlime,
	&shadowGoblin,
	&shadowKnight
};
#pragma endregion

#pragma endregion

#pragma region TURN

double playerFinalSpeed(Player* player, Persona* currentPersona)
{
	double bonus1 = 0, bonus2 = 0;
	double finalSpeed = currentPersona->speed;
	if (player->playerStatus.buff[2])
	{
		bonus1 = finalSpeed * 0.3;
	}
	if (player->playerStatus.debuff[2])
	{
		bonus2 = finalSpeed * 0.3;
	}
	return finalSpeed + bonus1 - bonus2;
}
double enemyFinalSpeed(Enemy* enemy)
{
	double bonus1 = 0, bonus2 = 0;
	double finalSpeed = enemy->enemyStatus.speed;
	if (enemy->enemyStatus.buff[2])
	{
		bonus1 = finalSpeed * 0.3;
	}
	if (enemy->enemyStatus.debuff[2])
	{
		bonus2 = finalSpeed * 0.3;
	}
	return finalSpeed + bonus1 - bonus2;
}
void initTurnOrder(TurnInfo turnOrder[], int* battleIndex, Player* player, Persona* currentPersona, NowEnemy* currentEnemyGroup)
{	// �ϴ� �÷��̾ �������
	turnOrder[*battleIndex].isPlayer = 1;
	turnOrder[*battleIndex].index = 0;
	turnOrder[*battleIndex].finalSpeed = playerFinalSpeed(player, currentPersona);
	(*battleIndex)++;
	// �� �������
	for (int i = 0; i < currentEnemyGroup->enemyNum; i++)
	{
		turnOrder[*battleIndex].isPlayer = 0;
		turnOrder[*battleIndex].index = i;
		turnOrder[*battleIndex].finalSpeed = enemyFinalSpeed(&currentEnemyGroup->enemyGroup[i]);
		(*battleIndex)++;	// �迭 ä��� + �� ����� ��Ʋ ������ �� �� ����
	}
	// finalSpeed ���� ������� ����!
	for (int i = 0; i < *battleIndex - 1; i++)	// battleIndex-1 ����ŭ �ݺ�,(�������ǲ����ص��Ǵϲ�...)
	{
		for (int j = 0; j < *battleIndex - 1 - i; j++)
		{
			if (turnOrder[j].finalSpeed < turnOrder[j + 1].finalSpeed)	// �������� �ڷ� �и�
			{
				TurnInfo temp;
				temp = turnOrder[j];
				turnOrder[j] = turnOrder[j + 1];
				turnOrder[j + 1] = temp;
			}
		}
	}
}
void playerTurn(Player* player, Persona* currentPersona, NowEnemy* currentEnemyGroup)
{
	Skill* nowSkill;
	char ch;
	char str[100];
	ch = '\0';
	str[0] = '\0';
	// �÷��̾� ��
	printf("---------------------------");
	printf("\n");
	// �� ���
	for (int i = 0; i < currentEnemyGroup->enemyNum; i++)
	{
		Enemy currentEnemy = currentEnemyGroup->enemyGroup[i];
		printf("���� ��: %s [%d / %d]\n", currentEnemy.enemyName, currentEnemy.enemyStatus.hp, currentEnemy.enemyStatus.hpMax);
	}
	// �޴� ����
	printf("\n~���� ����~\n");
	printf("HP: %d / %d\n", player->playerStatus.hp, player->playerStatus.hpMax);
	printf("MP: %d / %d\n\n", player->playerStatus.mp, player->playerStatus.mpMax);
	printf("�޴��� �����ϼ���...\n1. ��ų\n2. ����\n");
	scanf(" %c", &ch);

	switch (ch) {
	case '1': // ��ų
		printf("\n���� �丣�ҳ�: %s\n", currentPersona->personaName);
		printf("����� ��ų ����...\n\n");
		for (int i = 0; i < 8; i++) {
			printf("%s	", currentPersona->skillPool[i]->skillName);
			if (i % 2 != 0) {
				printf("\n");  
			}
		}
		nowSkill = checkSkill(player);
		useSkill(nowSkill, player, 1, player, currentEnemyGroup);
		// ���⿡ isEnemyDead �ְ������ useSkill���� �� ���� ����� �ְ� �ϱ⿡�� �ð��̾���...�Ф�
		break;
	case'2': // ����
		printf("������ ���� �����ϼ���...\n");
		Enemy target = currentEnemyGroup->enemyGroup[selectTarget(currentEnemyGroup)];
		int damage = calcAttackDamage(1, player, &target);
		attack(damage, &target); 
		printf("%s���� %d��ŭ�� �������� �������ϴ�...\n", target.enemyName, damage);
		break;
	default:
		printf("�߸��� �Է�\n");
		break;
	}
}
void enemyTurn(Player* player, Enemy* currentEnemy)
{
	int damage = currentEnemy->enemyStatus.stronger + rand() % 10;  // �⺻ ���� + �ణ ���� ������

	printf("%s�� �÷��̾ ����! [%d ������]\n", currentEnemy->enemyName, damage);
	Sleep(1000);
	// �÷��̾� �ǰ�
	player->playerStatus.hp -= damage;
	if (player->playerStatus.hp < 0) player->playerStatus.hp = 0;

	printf("�÷��̾� HP: %d / %d\n", player->playerStatus.hp, player->playerStatus.hpMax);
}

#pragma endregion

#pragma region BATTLE

int nextLevelExp[9] = {
	7, 21, 63, 189, 577, 1721, 2523, 3750, 5102
};

Skill* checkSkill(Player* player)
{
	char str[100];
	str[0] = '\0';
	int isExist = 0;
	do {
		scanf("%s", str);
		for (int i = 0; i < 8; i++)
		{
			if (player->personaList.playerPersona[player->personaList.nowPersona].skillPool[i] == NULL) continue; // Skill* NULL ���� üũ 
			if (!strcmp(str, player->personaList.playerPersona[player->personaList.nowPersona].skillPool[i]->skillName))
			{
				isExist = 1;
				return player->personaList.playerPersona[player->personaList.nowPersona].skillPool[i];
			}
		}
		printf("�ش� ��ų�� �������� �ʽ��ϴ�. �ٽ� �Է��Ͻʽÿ�...\n");
	} while (isExist == 0);
}

int selectTarget(NowEnemy* enemygroup)
{
	int choose = 0;
	while (1)
	{
		printf("������ ���� ��ȣ�� �Է�...(0���� ����)\n");
		scanf(" %d", &choose);
		if (choose >= 0 && choose < enemygroup->enemyNum)
		{
			return choose;
		}
		else
		{
			printf("�߸��� �Է��Դϴ�...\n");
			continue;
		}
	}
}
int isEnemyDead(Enemy enemy)
{
	if (enemy.enemyStatus.hp <= 0)
	{
		printf("%s óġ\n", enemy.enemyName);
		return 1;
	}
	return 0;
}
int isEnemyGroupDead(NowEnemy* currentEnemyGroup)
{
	for (int i = 0; i < currentEnemyGroup->enemyNum; i++)
	{
		if (currentEnemyGroup->enemyGroup[i].enemyStatus.hp > 0)
		{
			return 0;
		}
	}
	return 1; //���׾���
}
int isPlayerDead(Player* player)
{
	if (player->playerStatus.hp <= 0)
	{
		return 1;
	}
	return 0;
}
void setEnemyIndex(NowEnemy* currentEnemyGroup)
{
	int i = 0;
	while (i < currentEnemyGroup->enemyNum)
	{
		if (currentEnemyGroup->enemyGroup[i].enemyStatus.hp <= 0)
		{
			for (int j = i; j < currentEnemyGroup->enemyNum - 1; j++)
			{
				currentEnemyGroup->enemyGroup[j] = currentEnemyGroup->enemyGroup[j + 1];
			}
			(currentEnemyGroup->enemyNum)--;
		}
		else i++;
	}
}
void battle(Player* player)
{
	Persona* currentPersona = &player->personaList.playerPersona[player->personaList.nowPersona];

	NowEnemy currentenemyGroup;	//ememyNum, enemyGroup
	TurnInfo turnOrder[6]; // �� ����
	int battleIndex = 0;   // �Ѹ��?
	// �� ����
	currentenemyGroup = makeEnemy(); 
	NowEnemy* currentEnemyGroup = &currentenemyGroup;
	printf("---��Ʋ ����!!---\n");

	initTurnOrder(turnOrder, &battleIndex, player, currentPersona, currentEnemyGroup);
	while (!isPlayerDead(player) && !isEnemyGroupDead(currentEnemyGroup))	// 
	{
		int battleIndex = 0;
		initTurnOrder(turnOrder, &battleIndex, player, currentPersona, currentEnemyGroup);

		for (int i = 0; i < battleIndex; i++)
		{
			// �÷��̾� ��
			if (turnOrder[i].isPlayer)	
			{
				printf("\n>> %s�� ��...\n", player->playerName);
				playerTurn(player, currentPersona, currentEnemyGroup);
				if (isEnemyGroupDead(currentEnemyGroup))
				{
					// ���� ��~ �� ���� ����
					printf("�¸�!!!\n"); // ������, ����ġ ȹ�� ����
					currentenemyGroup = makeEnemy();
					Sleep(1000);
					printf("\n�� �� ������ �ٰ��ɴϴ�...\n");
					Sleep(1000);
				}
			}
			//�� ��
			else
			{
				Enemy* currentEnemy = &currentEnemyGroup->enemyGroup[turnOrder[i].index];
				if (currentEnemy->enemyStatus.hp <= 0)	continue;

				printf("\n>> %s�� ��...\n", currentEnemy->enemyName);
				enemyTurn(player, currentEnemy);
				Sleep(1000);
				if (player->playerStatus.hp == 0) // �� �� ���� �� �÷��̾� ��� �˻�
				{
					printf("\n����� ���������ϴ�...\n");
					exit(1);
					Sleep(10000);
				}
			}
		}
	}
}

#pragma endregion