# define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

# define SLASH 0
# define HIT 1
# define PENETRATE 2
# define FIRE 3
# define ICE 4
# define ELECTRIC 5
# define WIND 6
# define LIGHT 7
# define DARK 8
# define NONE 9

# define ALL_ENEMY 4
// ����� struct, type ����
typedef int index;	// ���߿� index�� int ��� index�� �ٲ� ��...
typedef int level;
typedef int stat;

// �ʿ� ����ġ �迭 [0]: 1 -> 2
int nextLevelExp[9];
typedef struct Level {
	level nowLevel;
	int nowExp;	//nowExp >= nextLevelExp[nowLevel-1] -> ������
}Level;
// ��ų ����

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
	int cost;	 // �� ��
	int target;
	int accuracy;
	int property; // ��ų �Ӽ�
}ImmediateDeath;
typedef struct heal {
	int cost;
	int amount;
	int target;
}Heal;
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

typedef enum skillType {
	PHYSICAL, MAGIC, IMDEATH, HEAL, BUFF, DEBUFF, DOUBLEP, ABNORMAL, NOSKILL
}SkillType;
typedef union skillTypeData {
	PhysicalAttack physic;
	MagicAttack magic;
	ImmediateDeath imDeath;
	Heal heal;
	Buff buff;
	DeBuff debuff;
	DoublePower doubleP;
	AbnormalStatus abnormal;
}SkillTypeData;

typedef struct skill {
	char skillName[100];
	SkillType skillType;
	SkillTypeData skillData;
}Skill;

// �丣�ҳ� ����
typedef struct persona {
	// �̸�, �ε���, ��, ��, ��, ��, ��, ����, ��ųǮ
	char personaName[100];
	index personaIndex;
	level personaLevel;
	stat stronger;
	stat intelligence;
	stat speed;
	stat duration;
	stat luck;
	int weekness[9];
	const Skill* skillPool[8];
}Persona;

// �÷��̾� ����
typedef struct playerstatus {	//player.h, aibo.h ���� ���, ���� �ɷ�ġ�� �丣�ҳ��� ���� �޶����Ƿ� ����
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int buff[3];	//��, ��, ��
	int debuff[3];
	int physicdouble; int magicdouble;
}PlayerStatus;
typedef struct playerPersonaList {
	Persona playerPersona[8];
	int numPersona;	//���� �丣�ҳ� ��
	int nowPersona;	//���� ������ �丣�ҳ� 
}PersonaList;
typedef struct player {
	char playerName[100];
	Level playerLevel;
	PlayerStatus playerStatus;
	PersonaList personaList;	
}Player;

// �� ����
typedef struct enemystatus {
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
}EnemyStatus;
typedef struct enemy{
	char enemyName[100];			// �� �̸�
	index enemyIndex;			// �� �ε���	
	EnemyStatus enemyStatus;
	const Skill* enemySkillPool[8];
	int enemyExp;				// ȹ�� ����ġ
	int enemyDropItem[3];		// ��� ������
}Enemy;

typedef struct nowEnemy {
	int enemyNum;
	Enemy enemyGroup[5];	
}NowEnemy;

Enemy* allEnemy[ALL_ENEMY];	// �׷� ������ ...
// ���� ���� ������ ��

// �Լ� ����
void initPlayer(Player* player);
NowEnemy makeEnemy();
Skill* checkSkill(Player* player);	
int selectTarget(Enemy EnemyGroup[]);
int isEnemyDead(Enemy enemy);
void setEnemyIndex(NowEnemy* currentEnemyGroup);
// Aibo selectTarget(Aibo target);
void useSkill(Skill* skill, Player* player, Persona* persona, NowEnemy* currentEnemyGroup);


int physicDouble(Player* player);
int magicDouble(Player* player);
int calcDamage(Skill* skill, Player* player, int amount, stat bonus);
void attack(int damage, Enemy* enemy);
void heal(Skill* skill, Player* player);
int imDeath(Skill* skill, Player* player, Enemy* enemy);


// ��ų ����
extern const Skill Noskill;
extern const Skill Slash;
extern const Skill Agi;
extern const Skill Bufu;
extern const Skill Zio;
extern const Skill Garu;
extern const Skill Megido;

extern const Skill Hama;

// �丣�ҳ� ����
extern Persona orpheus;
extern Persona empty;

// �� ����
extern Enemy testEnemy;