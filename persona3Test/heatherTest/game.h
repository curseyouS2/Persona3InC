#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// �Ӽ� ����
#define SLASH 0
#define HIT 1
#define PENETRATE 2
#define FIRE 3
#define ICE 4
#define ELECTRIC 5
#define WIND 6
#define LIGHT 7
#define DARK 8
#define NONE 9

// ���� ����
#define NA 0        // ����
#define WEAK 1      // ����       
#define RESIST 2    // ����(�ݰ���)
#define NODAMAGE 3      // ��ȿ
#define REPEL 4     // �ݻ�
#define ABSORB 5    // ���

// �⺻ Ÿ�� ����
typedef int level;

// ���� ���� (Forward Declaration)
typedef struct Skill Skill;
typedef struct Persona Persona;
typedef struct Player Player;
typedef struct Enemy Enemy;

// ���� ����ü
int nextLevelExp[9];
typedef struct Level {
    level nowLevel;
    int nowExp;
} Level;

// ��� ���� ����ü
// ��
typedef struct armor
{
    char name[100] ;
    int defense;
}Armor;
// ����
typedef struct weapon
{   // ���� �̸�, ���ݷ�, �Ӽ�(��, Ÿ, ��), ���߷�)
    char name[100] ;
    int power;
    int property;
    int accuracy;
}Weapon;
typedef struct equip
{
    Weapon weapon;
    Armor armor;
}Equip;


// ��ų ���� ����ü
typedef struct phycialttack {
    double cost;
    int amount;
    int times;
    int target;
    int accuracy;
    int property;
} PhysicalAttack;

typedef struct magicattack {
    int cost;
    int amount;
    int times;
    int target;
    int accuracy;
    int property;
} MagicAttack;

typedef struct immediatedeath {
    int cost;
    int target;
    int accuracy;
    int property;
} ImmediateDeath;

typedef struct heal {
    int cost;
    int amount;
    int target;
} Heal;

typedef struct buff {
    int cost;
    int bufftype;
    int target;
} Buff;

typedef Buff DeBuff;

typedef struct doublepower {
    int type;
} DoublePower;

typedef struct abnormalstatusskill {
    int cost;
    int target;
    int accuracy;
    int weirdtype;
} AbnormalStatus;

typedef enum skillType {
    PHYSICAL, MAGIC, IMDEATH, HEAL, BUFF, DEBUFF, DOUBLEP, ABNORMAL, NOSKILL
} SkillType;

typedef union skillTypeData {
    PhysicalAttack physic;
    MagicAttack magic;
    ImmediateDeath imDeath;
    Heal heal;
    Buff buff;
    DeBuff debuff;
    DoublePower doubleP;
    AbnormalStatus abnormal;
} SkillTypeData;

// ��ų ����ü
struct Skill {
    char skillName[100];
    SkillType skillType;
    SkillTypeData skillData;
};

// �丣�ҳ� ����ü
struct Persona {
    char personaName[100];
    int personaIndex;
    level personaLevel;
    int stronger;
    int intelligence;
    int speed;
    int duration;
    int luck;
    int weekness[9];
    const Skill* skillPool[8];
};

// �÷��̾� ���� ����ü��
typedef struct playerstatus {
    int hpMax;
    int mpMax;
    int hp;
    int mp;
    int buff[3];
    int debuff[3];
    int physicdouble;
    int magicdouble;
} PlayerStatus;

typedef struct playerPersonaList {
    Persona playerPersona[8];
    int numPersona;
    int nowPersona;
} PersonaList;

struct Player {
    char playerName[100];
    Level playerLevel;
    PlayerStatus playerStatus;
    PersonaList personaList;
    Equip equipment;
};

// �� ���� ����ü��
typedef struct enemystatus {
    int hpMax;
    int mpMax;
    int hp;
    int mp;
    int stronger;
    int intelligence;
    int speed;
    int duration;
    int luck;
    int weekness[9];
    int buff[3];
    int debuff[3];
    int physicdouble;
    int magicdouble;
} EnemyStatus;

struct Enemy {
    char enemyName[100];
    int enemyIndex;
    EnemyStatus enemyStatus;
    const Skill* enemySkillPool[8];
    int enemyExp;
    int enemyDropItem[3];
};

typedef struct nowEnemy {
    int enemyNum;
    Enemy enemyGroup[5];
} NowEnemy;

// �� ���� ����ü
typedef struct turninfo {
    int isPlayer;
    int index;
    double finalSpeed;
} TurnInfo;

// �Լ� ����
void initPlayer(Player* player);
NowEnemy makeEnemy();

int checkAttackWeakness(int isPlayer, Player* player, Persona* persona, Enemy* enemy, int damage);
int checkSkillWeakness(Skill* skill, int isPlayer, Player* player, Persona* persona, Enemy* enemy, int damage);

// �Ϲ� ���� �Լ�
int calcAttackDamage(int isPlayer, Player* player, Enemy* enemy);

// ��ų ���� �Լ���
void useSkill(const Skill* skill, void* attacker, int isPlayer, Player* player, NowEnemy* currentEnemyGroup);
int physicDouble(void* attacker, int isPlayer);
int magicDouble(void* attacker, int isPlayer);
int calcSkillDamage(const Skill* skill, void* attacker, int isPlayer, int amount, int statBonus);
void attack(int damage, Enemy* enemy);
void attackPlayer(int damage, Player* player);
void heal(Skill* skill, Player* player);
void healEnemy(Skill* skill, Enemy* enemy);
int imDeath(const Skill* skill, void* attacker, int isPlayer, Player* player, Enemy* enemy);

// �� ���� �Լ���
double playerFinalSpeed(Player* player, Persona* currentPersona);
double enemyFinalSpeed(Enemy* enemy);
void initTurnOrder(TurnInfo turnOrder[], int* battleIndex, Player* player, Persona* currentPersona, NowEnemy* currentEnemyGroup);
void playerTurn(Player* player, Persona* currentPersona, NowEnemy* currentEnemyGroup);
void enemyTurn(Player* player, Enemy* currentEnemy);

// ��Ʋ ���� �Լ���
Skill* checkSkill(Player* player);
int selectTarget(NowEnemy* enemygroup);
int isEnemyDead(Enemy enemy);
int isEnemyGroupDead(NowEnemy* currentEnemyGroup);
int isPlayerDead(Player* player);
void setEnemyIndex(NowEnemy* currentEnemyGroup);
void battle(Player* player);

// ���� ���⿡ ���� ��ȭ
// ���� ���� ����
#define ALL_ENEMY 4
extern Enemy* allEnemy[ALL_ENEMY];

// ��� extern
extern const Weapon normalSword;
extern const Armor normalArmor;

// ��ų extern 
extern const Skill Noskill;
extern const Skill Slash;
extern const Skill Agi;
extern const Skill Bufu;
extern const Skill Zio;
extern const Skill Garu;
extern const Skill Megido;
extern const Skill Hama;
extern const Skill Dia;

// �丣�ҳ� extern 
extern Persona orpheus;
extern Persona empty;

// �� extern 
extern Enemy testEnemy;
extern Enemy shadowSlime;
extern Enemy shadowGoblin;
extern Enemy shadowKnight;