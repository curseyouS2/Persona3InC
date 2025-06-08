#include "game.h"


// 약점, 내성 체크 함수 (calcDamage에 넣을거임)
int checkAttackWeakness(int isPlayer, Player* player, Persona* persona, Enemy* enemy, int damage)
{
	if (isPlayer)
	{
		int property = player->equipment.weapon.property;
		if (enemy->enemyStatus.weekness[property] != 0)
		{
			switch (enemy->enemyStatus.weekness[property])
			{
			case 1:	// 약점
				printf("%s의 약점에 명중했다!\n", enemy->enemyName);
				return damage * 1.5;
			case 2: // 경감
				printf("%s에게 데미지가 반감되었다...\n", enemy->enemyName);
				return damage * 0.5;
			case 3: // 무효
				printf("%s에게는 통하지 않는다...\n", enemy->enemyName);
				return 0;
			case 4: // 반사
				player->playerStatus.hp -= damage;
				isPlayerDead(player);
				printf("%s는 공격을 반사했다!\n", enemy->enemyName);
				return 0;
			case 5: // 흡수
				enemy->enemyStatus.hp = +damage;
				if (enemy->enemyStatus.hp > enemy->enemyStatus.hpMax) enemy->enemyStatus.hp = enemy->enemyStatus.hpMax;
				printf("%s은 공격을 흠수했다...\n", enemy->enemyName);
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
			case 1:	// 약점
				printf("%s의 약점에 명중했다!\n", player->playerName);
				return damage * 1.5;
			case 2: // 경감
				printf("%s에게 데미지가 반감되었다...\n", player->playerName);
				return damage * 0.5;
			case 3: // 무효
				printf("%s에게는 통하지 않는다...\n", player->playerName);
				return 0;
			case 4: // 반사
				player->playerStatus.hp -= damage;
				isPlayerDead(player);
				printf("%s는 공격을 반사했다!\n", player->playerName);
				return 0;
			case 5: // 흡수
				player->playerStatus.hp = +damage;
				if (player->playerStatus.hp > player->playerStatus.hpMax) player->playerStatus.hp = player->playerStatus.hpMax;
				printf("%s은 공격을 흠수했다...\n", player->playerName);
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
			case 1:	// 약점
				printf("%s의 약점에 명중했다!\n", enemy->enemyName);
				return damage * 1.5;
			case 2: // 경감
				printf("%s에게 데미지가 반감되었다...\n", enemy->enemyName);
				return damage * 0.5;
			case 3: // 무효
				printf("%s에게는 통하지 않는다...\n", enemy->enemyName);
				return 0;
			case 4: // 반사
				player->playerStatus.hp -= damage;
				isPlayerDead(player);
				printf("%s는 공격을 반사했다!\n", enemy->enemyName);
				return 0;
			case 5: // 흡수
				enemy->enemyStatus.hp = +damage;
				if (enemy->enemyStatus.hp > enemy->enemyStatus.hpMax) enemy->enemyStatus.hp = enemy->enemyStatus.hpMax;
				printf("%s은 공격을 흠수했다...\n", enemy->enemyName);
				return 0;
			}
		}
	}
	else // 적의 경우
	{
		if (persona->weekness[0] != 0)
		{
			switch (persona->weekness[0])
			{
			case 1:	// 약점
				printf("%s의 약점에 명중했다!\n", player->playerName);
				return damage * 1.5;
			case 2: // 경감
				printf("%s에게 데미지가 반감되었다...\n", player->playerName);
				return damage * 0.5;
			case 3: // 무효
				printf("%s에게는 통하지 않는다...\n", player->playerName);
				return 0;
			case 4: // 반사
				player->playerStatus.hp -= damage;
				isPlayerDead(player);
				printf("%s는 공격을 반사했다!\n", player->playerName);
				return 0;
			case 5: // 흡수
				player->playerStatus.hp = +damage;
				if (player->playerStatus.hp > player->playerStatus.hpMax) player->playerStatus.hp = player->playerStatus.hpMax;
				printf("%s은 공격을 흠수했다...\n", player->playerName);
				return 0;
			}
		}
	}
}
// 회피 함수 (imDeath랑 비슷하게 가면 될듯하다...상관 요소: 약점, 속도버프...attack 내부에 넣을거임)

#pragma region EQUIP
const Weapon normalSword = { "평범한 검", 15, SLASH, 98 };
const Armor normalArmor = { "평범한 갑옷", 30 };

// 장비 교체 함수 만들어야됨
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
	if (isPlayer) //플레이어 턴
	{
		Player* player = (Player*)attacker;
		if (player->playerStatus.physicdouble)
		{
			player->playerStatus.physicdouble = 0;
			return 1;
		}
		else return 0;
	}
	else // 적 턴
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
	if (isPlayer)	//플레이어 턴
	{
		Player* player = (Player*)attacker;
		if (player->playerStatus.magicdouble)
		{
			player->playerStatus.magicdouble = 0;
			return 1;
		}
		else return 0;
	}
	else // 적 턴 
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

// 스킬 데미지 계산
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

	// 공격 주체에 따른 초기 설정
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

	if (isAttackBuff || isAttackDebuff)	//공격력 버프디버프 있다면
	{
		int attackBuffBonus = 0.3 * damage;
		int attackDebuffBonus = 0.3 * damage;
		if (isAttackBuff) damage += attackBuffBonus;
		if (isAttackDebuff) damage -= attackDebuffBonus;
	}
	// 2배 연산 가장 마지막에
	if (skill->skillType == PHYSICAL && isPhysicdouble) damage *= 2;
	if (skill->skillType == MAGIC && isMagicdouble) damage *= 2;

	return damage;
}

// 실제로 공격	... 명중 확률 계산, 
void attack(int damage, Enemy* enemy)
{
	enemy->enemyStatus.hp -= damage;
	Sleep(1000);
}
void attackPlayer(int damage, Player* player)
{
	player->playerStatus.hp -= damage;
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
void healEnemy(Skill* skill, Enemy* enemy)	//나중에 aibo 추가할 것 아니면 aibo랑 enemy랑 같은 구조로 짜는게 나을지도
{
	int currentHp = enemy->enemyStatus.hp,
		healAmount = skill->skillData.heal.amount,
		maxHp = enemy->enemyStatus.hpMax;
	currentHp += healAmount;
	if (currentHp > maxHp)	currentHp = maxHp;
	printf("\n%s이 %d만큼 회복함\n", enemy->enemyName, healAmount);
	enemy->enemyStatus.hp = currentHp;
}

// 즉사기 확률 계산 
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

	// 랜덤값이 realChance보다 크면 실패...realChance가 클수록 맞기 어렵겠죠?
	int nowChance = rand() % 100 + 1;    // 1부터 100까지

	if (nowChance > realChance)
	{
		return 0;    // 실패
	}
	else
	{
		return 1;    // 성공
	}
}

// 스킬 사용

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
				printf("%s 사용!\n", skill->skillName);
				attack(damage, e);
				printf("%s에게 %d만큼의 데미지를 입혔습니다...\n", e->enemyName, damage);
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

			printf("%s 사용!\n", skill->skillName);
			attackPlayer(damage, player); // 여기서 player 매개변수 사용 (필수!)
			printf("플레이어에게 %d만큼의 데미지를 입혔습니다...\n", damage);
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
				printf("%s 사용!\n", skill->skillName);
				attack(damage, e);
				printf("%s에게 %d만큼의 데미지를 입혔습니다...\n", e->enemyName, damage);
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

			printf("%s 사용!\n", skill->skillName);
			attackPlayer(damage, player);
			printf("플레이어에게 %d만큼의 데미지를 입혔습니다...\n", damage);
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
				printf("%s 사용!\n", skill->skillName);

				if (imDeath(skill, attacker, isPlayer, player, e))	// 확률계산함수
				{
					attack(e->enemyStatus.hpMax, e);
					printf("%s 명중!\n", skill->skillName);
					if (isEnemyDead(*e))
					{
						setEnemyIndex(currentEnemyGroup);	//적 죽으면 적 그룹 인덱스 정렬
					}
				}
				else
				{
					printf("%s 빗나감!\n", skill->skillName);
				}
			}
		}
		else // 적의 공격
		{
			attackerEnemy->enemyStatus.mp -= cost;

			printf("%s 사용!\n", skill->skillName);
			if (imDeath(skill, attacker, isPlayer, player, NULL))	// 확률계산함수
			{
				attackPlayer(player->playerStatus.hpMax, player);
				printf("%s 명중!\n", skill->skillName);
				if (isPlayerDead(player))
				{
					printf("게임오버...\n");
				}
			}
			else
			{
				printf("%s 빗나감!\n", skill->skillName);
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
					printf("%s 사용!\n", skill->skillName);
					attackerPlayer->playerStatus.buff[skill->skillData.buff.bufftype] = 3;
				}
			}
			else // 적이 버프 사용 시
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
				printf("%s 사용!\n", skill->skillName);

				attackerPlayer->playerStatus.mp -= skill->skillData.debuff.cost;
				if (skill->skillData.debuff.target == 0)
				{
					e->enemyStatus.debuff[skill->skillData.debuff.bufftype] = 3;
				}

			}

		}
		else // 적이 버프 사용 시
		{
			attackerEnemy->enemyStatus.mp -= skill->skillData.debuff.cost;
			if (skill->skillData.debuff.target == 0)
			{
				printf("%s가 %s 사용!\n", attackerEnemy->enemyName, skill->skillName);
				player->playerStatus.debuff[skill->skillData.debuff.bufftype] = 3;
			}
		}
		break;
#pragma endregion

	#pragma region DOUBLEP
	case DOUBLEP:
		if (isPlayer) //플레이어 턴
		{
			if (skill->skillData.doubleP.type == 0) //차지
			{
				if (attackerPlayer->playerStatus.physicdouble == 0)
				{
					attackerPlayer->playerStatus.physicdouble = 1;
					printf("%s 사용! \n", skill->skillName);
					printf("%s가 다음에 사용하는 물리 스킬의 위력이 2배가 된다...\n", attackerPlayer->playerName);
				}
				else
				{
					printf("%s는 이미 적용되어있다!\n", skill->skillName);
				}
			}

			if (skill->skillData.doubleP.type == 1) // 컨센트레이트
			{
				if (attackerPlayer->playerStatus.magicdouble == 0)
				{
					attackerPlayer->playerStatus.magicdouble = 1;
					printf("%s 사용! \n", skill->skillName);
					printf("%s가 다음에 사용하는 마법 스킬의 위력이 2배가 된다...\n", attackerPlayer->playerName);
				}
				else
				{
					printf("%s는 이미 적용되어있다!\n", skill->skillName);
				}
			}
		}
		else // 적 턴
		{
			if (skill->skillData.doubleP.type == 0) //차지
			{
				if (attackerEnemy->enemyStatus.physicdouble == 0)
				{
					attackerEnemy->enemyStatus.physicdouble = 1;
					printf("%s 사용! \n", skill->skillName);
					printf("%s가 다음에 사용하는 물리 스킬의 위력이 2배가 된다...\n", attackerEnemy->enemyName);
				}
				else
				{
					printf("%s는 이미 적용되어있다!\n", skill->skillName);
				}
			}

			if (skill->skillData.doubleP.type == 1) //컨센트레이트
			{
				if (attackerEnemy->enemyStatus.physicdouble == 0)
				{
					attackerEnemy->enemyStatus.magicdouble = 1;
					printf("%s 사용! \n", skill->skillName);
					printf("%s가 다음에 사용하는 마법 스킬의 위력이 2배가 된다...\n", attackerEnemy->enemyName);
				}
				else
				{
					printf("%s는 이미 적용되어있다!\n", skill->skillName);
				}
			}
		}
		break;
#pragma endregion

	case ABNORMAL: // 나중에 구현...
		break;
	}

}

// 스킬 구현
	#pragma region SkillDescription
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
const Skill Megido = { "디버그스킬", MAGIC, {.magic = {50, 200, 1, 0, 90, NONE}} };

const Skill Hama = { "하마", IMDEATH, {.imDeath = {20, 0, 80, LIGHT}} };

const Skill Dia = { "디아", HEAL, {.heal = {20, 50, 1,}} };
#pragma endregion

#pragma endregion

#pragma region PERSONA
// 페르소나 구현
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
	"빈 슬롯", 0, 00,
	0, 0, 0, 0, 0,
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{&Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill}
};
Persona orpheus = {
	"오르페우스", 1, 10,
	2, 2, 2, 2, 2,
	{0, 0, 0, 0, 0, WEAK, 0, 0, WEAK},
	{&Slash, &Agi, &Bufu, &Zio, &Garu, &Megido, &Hama, &Dia}
};
#pragma endregion
#pragma endregion

#pragma region PLAYER
void initPlayer(Player* player)
{
	strcpy(player->playerName, "유키");
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
	for (int i = 0; i < newEnemyGroup.enemyNum; i++)	// allEnemy배열
	{
		newEnemyGroup.enemyGroup[i] = *allEnemy[rand() % ALL_ENEMY];
	}
	return newEnemyGroup;
}

// 적 구현
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
	{0,0,0,0,0,0,0,0,0},{0,0,0}, {0,0,0}, 0, 0},
	{&Slash, &Agi, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	25, {0, 0, 1}
};
Enemy shadowSlime = {
	"섀도우 슬라임", 1,
	{80, 80, 80, 80, 8, 5, 1, 5, 5,
	{0,0,0,0,0,0,0,WEAK,0}, {0,0,0}, {0,0,0}, 0, 0},
	{&Slash, &Bufu, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	15, {0, 1, 2}
};
Enemy shadowGoblin = {
	"섀도우 고블린", 2,
	{120, 50, 120, 50, 12, 1, 10, 8, 6,
	{WEAK,0,0,1,2,3,4,0,0}, {0,0,0}, {0,0,0}, 0, 0},
	{&Zio, &Slash, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill, &Noskill},
	30, {1, 2, 3}
};
Enemy shadowKnight = {
	"섀도우 나이트", 3,
	{200, 100, 200, 100, 20, 15, 12, 10, 10,
	{0,0,0,0,WEAK,0,0,0,0}, {0,0,0}, {0,0,0}, 0, 0},
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
{	// 일단 플레이어를 집어넣음
	turnOrder[*battleIndex].isPlayer = 1;
	turnOrder[*battleIndex].index = 0;
	turnOrder[*battleIndex].finalSpeed = playerFinalSpeed(player, currentPersona);
	(*battleIndex)++;
	// 적 집어넣음
	for (int i = 0; i < currentEnemyGroup->enemyNum; i++)
	{
		turnOrder[*battleIndex].isPlayer = 0;
		turnOrder[*battleIndex].index = i;
		turnOrder[*battleIndex].finalSpeed = enemyFinalSpeed(&currentEnemyGroup->enemyGroup[i]);
		(*battleIndex)++;	// 배열 채우기 + 총 몇명이 배틀 중인지 알 수 있음
	}
	// finalSpeed 높은 순서대로 정렬!
	for (int i = 0; i < *battleIndex - 1; i++)	// battleIndex-1 수만큼 반복,(마지막건꼭안해도되니께...)
	{
		for (int j = 0; j < *battleIndex - 1 - i; j++)
		{
			if (turnOrder[j].finalSpeed < turnOrder[j + 1].finalSpeed)	// 느릴수록 뒤로 밀림
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
	// 플레이어 턴
	printf("---------------------------");
	printf("\n");
	// 적 출력
	for (int i = 0; i < currentEnemyGroup->enemyNum; i++)
	{
		Enemy currentEnemy = currentEnemyGroup->enemyGroup[i];
		printf("현재 적: %s [%d / %d]\n", currentEnemy.enemyName, currentEnemy.enemyStatus.hp, currentEnemy.enemyStatus.hpMax);
	}
	// 메뉴 선택
	printf("\n~현재 상태~\n");
	printf("HP: %d / %d\n", player->playerStatus.hp, player->playerStatus.hpMax);
	printf("MP: %d / %d\n\n", player->playerStatus.mp, player->playerStatus.mpMax);
	printf("메뉴를 선택하세요...\n1. 스킬\n2. 공격\n");
	scanf(" %c", &ch);

	switch (ch) {
	case '1': // 스킬
		printf("\n현재 페르소나: %s\n", currentPersona->personaName);
		printf("사용할 스킬 선택...\n\n");
		for (int i = 0; i < 8; i++) {
			printf("%s	", currentPersona->skillPool[i]->skillName);
			if (i % 2 != 0) {
				printf("\n");  
			}
		}
		nowSkill = checkSkill(player);
		useSkill(nowSkill, player, 1, player, currentEnemyGroup);
		// 여기에 isEnemyDead 넣고싶은데 useSkill에서 다 뺴고 여기다 넣고 하기에는 시간이없다...ㅠㅠ
		break;
	case'2': // 공격
		printf("공격할 적을 선택하세요...\n");
		Enemy target = currentEnemyGroup->enemyGroup[selectTarget(currentEnemyGroup)];
		int damage = calcAttackDamage(1, player, &target);
		attack(damage, &target); 
		printf("%s에게 %d만큼의 데미지를 입혔습니다...\n", target.enemyName, damage);
		break;
	default:
		printf("잘못된 입력\n");
		break;
	}
}
void enemyTurn(Player* player, Enemy* currentEnemy)
{
	int damage = currentEnemy->enemyStatus.stronger + rand() % 10;  // 기본 공격 + 약간 랜덤 데미지

	printf("%s가 플레이어를 공격! [%d 데미지]\n", currentEnemy->enemyName, damage);
	Sleep(1000);
	// 플레이어 피격
	player->playerStatus.hp -= damage;
	if (player->playerStatus.hp < 0) player->playerStatus.hp = 0;

	printf("플레이어 HP: %d / %d\n", player->playerStatus.hp, player->playerStatus.hpMax);
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
	int choose = 0;
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
int isEnemyGroupDead(NowEnemy* currentEnemyGroup)
{
	for (int i = 0; i < currentEnemyGroup->enemyNum; i++)
	{
		if (currentEnemyGroup->enemyGroup[i].enemyStatus.hp > 0)
		{
			return 0;
		}
	}
	return 1; //다죽었음
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
	TurnInfo turnOrder[6]; // 턴 순서
	int battleIndex = 0;   // 총몇명?
	// 적 생성
	currentenemyGroup = makeEnemy(); 
	NowEnemy* currentEnemyGroup = &currentenemyGroup;
	printf("---배틀 개시!!---\n");

	initTurnOrder(turnOrder, &battleIndex, player, currentPersona, currentEnemyGroup);
	while (!isPlayerDead(player) && !isEnemyGroupDead(currentEnemyGroup))	// 
	{
		int battleIndex = 0;
		initTurnOrder(turnOrder, &battleIndex, player, currentPersona, currentEnemyGroup);

		for (int i = 0; i < battleIndex; i++)
		{
			// 플레이어 턴
			if (turnOrder[i].isPlayer)	
			{
				printf("\n>> %s의 턴...\n", player->playerName);
				playerTurn(player, currentPersona, currentEnemyGroup);
				if (isEnemyGroupDead(currentEnemyGroup))
				{
					// 전투 끝~ 새 전투 시작
					printf("승리!!!\n"); // 아이템, 경험치 획득 로직
					currentenemyGroup = makeEnemy();
					Sleep(1000);
					printf("\n새 적 무리가 다가옵니다...\n");
					Sleep(1000);
				}
			}
			//적 턴
			else
			{
				Enemy* currentEnemy = &currentEnemyGroup->enemyGroup[turnOrder[i].index];
				if (currentEnemy->enemyStatus.hp <= 0)	continue;

				printf("\n>> %s의 턴...\n", currentEnemy->enemyName);
				enemyTurn(player, currentEnemy);
				Sleep(1000);
				if (player->playerStatus.hp == 0) // 적 턴 끝날 때 플레이어 사망 검사
				{
					printf("\n당신은 쓰러졌습니다...\n");
					exit(1);
					Sleep(10000);
				}
			}
		}
	}
}

#pragma endregion