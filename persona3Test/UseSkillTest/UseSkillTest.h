#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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


// ����� struct, type ����
typedef char name;
typedef int index;	// ���߿� index�� int ��� index�� �ٲ� ��...
typedef int level;
typedef int stat;

// �ʿ� ����ġ �迭 [0]: 1 -> 2
int nextLevelExp[9] = {
	7, 21, 63, 189, 577, 1721, 2523, 3750, 5102
};
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
	PHYSICAL, MAGIC, IMDEATH, HEAL, BUFF, DEBUFF, DOUBLEP, ABNORMAL
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
	name skillname[100];
	SkillType skillType;
	SkillTypeData skillData;
}Skill;

// �丣�ҳ� ����
typedef struct persona {
	// �̸�, �ε���, ��, ��, ��, ��, ��, ����, ��ųǮ
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
	name playerName[100];
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
	name enemyName[20];			// �� �̸�
	index enemyIndex;			// �� �ε���	
	EnemyStatus enemyStatus;
	int enemyExp;				// ȹ�� ����ġ
	int enemyDropItem[3];		// ��� ������
}Enemy;

// �Լ� ����
void initPlayer(Player* player);

int physicDouble(Player* player);
int magicDouble(Player* player);
int calcDamage(Skill* skill, Player* player, int amount, stat bonus);
void attack(int damage, Enemy* enemy);
void heal(Skill* skill, Player* player);
int imDeath(Skill* skill, Player* player, Enemy* enemy);
void useSkill(Skill* skill, Player* player, Persona* persona, Enemy* enemy);

// �丣�ҳ� ����
Persona orpheus;
Persona empty;