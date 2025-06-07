#include "UseSkillTest.h"
int nextLevelExp[9] = {
	7, 21, 63, 189, 577, 1721, 2523, 3750, 5102
};
void initPlayer(Player* player) 
{
	strcpy(player->playerName, "유키");
	player->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	
	player->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty }, 1, 0 };  // numPersona, nowpersona
}

NowEnemy makeEnemy() {
	srand(time(NULL));
	NowEnemy newEnemyGroup;
	newEnemyGroup.enemyNum = rand() % 5 + 1;
	for (int i = 0; i < newEnemyGroup.enemyNum; i++)	// allEnemy배열
	{
		newEnemyGroup.enemyGroup[i] = *allEnemy[rand() % ALL_ENEMY];
	}
	return newEnemyGroup;
}

Skill* checkSkill(Player* player)
{
	char str[100];
	str[0] = '\0';
	int isExist = 0;
	do {
		scanf("%s", str);
		for (int i = 0;i < 8;i++) 
		{
			if (player->personaList.playerPersona[player->personaList.nowPersona].skillPool[i] == NULL) continue; // Skill* NULL 인지 체크 
			if (!strcmp(str, player->personaList.playerPersona[player->personaList.nowPersona].skillPool[i]->skillName))
			{
				isExist = 1;
				return player->personaList.playerPersona[player->personaList.nowPersona].skillPool[i];
			}
		}
		printf("해당 스킬은 존재하지 않습니다. 다시 입력하십시오...\n");
	} while (isExist == 0);
}

int selectTarget(NowEnemy* enemygroup)
{
	int choose;
	while (1)
	{
		printf("공격할 적의 번호를 입력...(0부터 시작)\n");
		scanf(" %d", &choose);
		if (choose >= 0 && choose < enemygroup->enemyNum)
		{
			return choose;
		}
		else
		{
			printf("잘못된 입력입니다...\n");
			continue;
		}
	}
}

int isEnemyDead(Enemy enemy)
{
	if (enemy.enemyStatus.hp <= 0)
	{
		printf("%s 처치\n", enemy.enemyName);
		return 1;
	}
	return 0;
}
void setEnemyIndex(NowEnemy* currentEnemyGroup)
{
	for (int i = 0; i < currentEnemyGroup->enemyNum; i++)
	{
		if (currentEnemyGroup->enemyGroup[i].enemyStatus.hp <= 0)
		{
			currentEnemyGroup->enemyGroup[i] = currentEnemyGroup->enemyGroup[i + 1];
		}
	}
	(currentEnemyGroup->enemyNum)--;
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
	enemy->enemyStatus.hp -= damage;
}
// 힐 적용
void heal(Skill* skill, Player* player)	//나중에 aibo 추가할 것 아니면 aibo랑 enemy랑 같은 구조로 짜는게 나을지도
{
	int currentHp = player->playerStatus.hp,
		healAmount = skill->skillData.heal.amount,
		maxHp = player->playerStatus.hpMax;
	currentHp += healAmount;
	if (currentHp > maxHp)	currentHp = maxHp;
	printf("\n%d만큼 회복함\n", healAmount);
	player->playerStatus.hp = currentHp;
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
		return 0;
	}
	else
	{
		return 1;
	}
}

// 스킬 사용
void useSkill(Skill* skill, Player* player, Persona* persona, NowEnemy* currentEnemyGroup)
{
	int damage = 0;
	int cost = 0;
	switch (skill->skillType) {

	case PHYSICAL:
		cost = (skill->skillData.physic.cost) * (player->playerStatus.hpMax);
		player->playerStatus.hp -= cost;
		damage = calcDamage(skill, player, skill->skillData.physic.amount, persona->stronger);
		if (skill->skillData.physic.target == 0)
		{
			int choose = selectTarget(currentEnemyGroup);
			Enemy* e = &currentEnemyGroup->enemyGroup[choose];
			printf("%s 사용!\n", skill->skillName);
			attack(damage, e);
			printf("%s에게 %d만큼의 데미지를 입혔습니다...\n", currentEnemyGroup->enemyGroup[choose], damage);
			if (isEnemyDead(currentEnemyGroup->enemyGroup[choose])) {
				setEnemyIndex(currentEnemyGroup);
			}
		}
		break;

	case MAGIC:
		cost = skill->skillData.magic.cost;
		player->playerStatus.mp -= cost;
		damage = calcDamage(skill, player, skill->skillData.magic.amount, persona->intelligence);
		if (skill->skillData.magic.target == 0)
		{
			int choose = selectTarget(currentEnemyGroup);
			Enemy* e = &currentEnemyGroup->enemyGroup[choose];
			printf("%s 사용!\n", skill->skillName);
			attack(damage, e);
			printf("%s에게 %d만큼의 데미지를 입혔습니다...\n", currentEnemyGroup->enemyGroup[choose], damage);
			if (isEnemyDead(currentEnemyGroup->enemyGroup[choose])) {
				setEnemyIndex(currentEnemyGroup);
			}
		}
		break;

	case IMDEATH:
		cost = skill->skillData.imDeath.cost;
		player->playerStatus.mp -= cost;
		if (skill->skillData.physic.target == 0)	// 단일 타겟
		{
			int choose = selectTarget(currentEnemyGroup);
			Enemy* e = &currentEnemyGroup->enemyGroup[choose];
			printf("%s 사용!\n", skill->skillName);
			if (imDeath(skill, player, e))	// 명중시에
			{
				attack(e->enemyStatus.hpMax, e);	// 적 전체 체력만큼 데미지
				printf("%s 명중!\n", skill->skillName);
				if (isEnemyDead(currentEnemyGroup->enemyGroup[choose])) 
				{
					setEnemyIndex(currentEnemyGroup);
				}
			}
			else
			{
				printf("%s 빗나감!\n", skill->skillName);
			}
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
const Skill Noskill = { "빈 슬롯", NOSKILL, {.physic = {0, 0, 0, 0, 0, SLASH}} };

const Skill Slash = { "슬래쉬", PHYSICAL, {.physic = {0.07, 50, 1, 0, 100, SLASH}} };
const Skill Agi = { "아기", MAGIC, {.magic = {10, 50, 1, 0, 50, FIRE}} };
const Skill Bufu = { "부흐", MAGIC, {.magic = {10, 50, 1, 0, 50, ICE}} };
const Skill Zio = { "지오", MAGIC, {.magic = {10, 50, 1, 0, 50, ELECTRIC}} };
const Skill Garu = { "갈", MAGIC, {.magic = {10, 50, 1, 0, 50, WIND}} };
const Skill Megido = { "메기도", MAGIC, {.magic = {50, 150, 1, 1, 90, NONE}} };

const Skill Hama = { "하마", IMDEATH, {.imDeath = {20, 0, 30, LIGHT}} };

const Skill Dia = { "디아", HEAL, {.heal = {20, 30, 1,}} };

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

Persona empty = {
	"빈 슬롯", 0, 00,
	0, 0, 0, 0, 0,
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{&Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill}
};

Persona orpheus = {
	"오르페우스", 1, 10,
	10, 10, 10, 10, 10,
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{&Slash, &Agi, &Bufu, &Zio, &Garu, &Megido, &Hama, &Dia}
};

// 적 구현
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
	int buff[3];	//공, 방, 속
	int debuff[3];
Enemy
	char enemyName[100];			// 적 이름
	index enemyIndex;			// 적 인덱스	
	EnemyStatus enemyStatus;
	int enemyExp;				// 획득 경험치
	int enemyDropItem[3];		// 드롭 아이템

*/

Enemy testEnemy = {
	"테스트용 적", 0,
	{100, 100, 100, 100, 10, 10, 10, 10, 10,
	{0,0,0,0,0,0,0,0,0},{0,0,0}, {0,0,0}},
	{&Slash, &Agi, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	25, {0, 0, 1}
};

Enemy shadowSlime = {
	"섀도우 슬라임", 1,
	{80, 80, 80, 80, 8, 5, 6, 5, 5,
	{0,0,0,0,0,0,0,1,1}, {0,0,0}, {0,0,0}},
	{&Slash, &Bufu, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	15, {0, 1, 2}
};

Enemy shadowGoblin = {
	"섀도우 고블린", 2,
	{120, 50, 120, 50, 12, 8, 10, 8, 6,
	{0,0,1,1,0,0,0,0,0}, {0,0,0}, {0,0,0}},
	{&Zio, &Slash, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	30, {1, 2, 3}
};

Enemy shadowKnight = {
	"섀도우 나이트", 3,
	{200, 100, 200, 100, 20, 15, 12, 10, 10,
	{1,1,0,0,0,0,0,0,1}, {0,0,0}, {0,0,0}},
	{&Slash, &Garu, &Bufu, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	50, {2, 3, 4}
};
 

// 전체 적 저장 배열
Enemy* allEnemy[ALL_ENEMY] = {
	&testEnemy,
	&shadowSlime,
	&shadowGoblin,
	&shadowKnight
};
