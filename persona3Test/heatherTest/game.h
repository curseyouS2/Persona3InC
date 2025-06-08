#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// 속성 정의
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

// 내성 정의
#define NA 0        // 없음
#define WEAK 1      // 약점       
#define RESIST 2    // 저항(반감됨)
#define NODAMAGE 3      // 무효
#define REPEL 4     // 반사
#define ABSORB 5    // 흠수

// 기본 타입 정의
typedef int level;

// 전방 선언 (Forward Declaration)
typedef struct Skill Skill;
typedef struct Persona Persona;
typedef struct Player Player;
typedef struct Enemy Enemy;

// 레벨 구조체
int nextLevelExp[9];
typedef struct Level {
    level nowLevel;
    int nowExp;
} Level;

// 장비 관련 구조체
// 방어구
typedef struct armor
{
    char name[100] ;
    int defense;
}Armor;
// 무기
typedef struct weapon
{   // 무기 이름, 공격력, 속성(참, 타, 관), 명중률)
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


// 스킬 관련 구조체
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

// 스킬 구조체
struct Skill {
    char skillName[100];
    SkillType skillType;
    SkillTypeData skillData;
};

// 페르소나 구조체
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

// 플레이어 관련 구조체들
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

// 적 관련 구조체들
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

// 턴 정보 구조체
typedef struct turninfo {
    int isPlayer;
    int index;
    double finalSpeed;
} TurnInfo;

// 함수 선언
void initPlayer(Player* player);
NowEnemy makeEnemy();

int checkAttackWeakness(int isPlayer, Player* player, Persona* persona, Enemy* enemy, int damage);
int checkSkillWeakness(Skill* skill, int isPlayer, Player* player, Persona* persona, Enemy* enemy, int damage);

// 일반 공격 함수
int calcAttackDamage(int isPlayer, Player* player, Enemy* enemy);

// 스킬 관련 함수들
void useSkill(const Skill* skill, void* attacker, int isPlayer, Player* player, NowEnemy* currentEnemyGroup);
int physicDouble(void* attacker, int isPlayer);
int magicDouble(void* attacker, int isPlayer);
int calcSkillDamage(const Skill* skill, void* attacker, int isPlayer, int amount, int statBonus);
void attack(int damage, Enemy* enemy);
void attackPlayer(int damage, Player* player);
void heal(Skill* skill, Player* player);
void healEnemy(Skill* skill, Enemy* enemy);
int imDeath(const Skill* skill, void* attacker, int isPlayer, Player* player, Enemy* enemy);

// 턴 관련 함수들
double playerFinalSpeed(Player* player, Persona* currentPersona);
double enemyFinalSpeed(Enemy* enemy);
void initTurnOrder(TurnInfo turnOrder[], int* battleIndex, Player* player, Persona* currentPersona, NowEnemy* currentEnemyGroup);
void playerTurn(Player* player, Persona* currentPersona, NowEnemy* currentEnemyGroup);
void enemyTurn(Player* player, Enemy* currentEnemy);

// 배틀 관련 함수들
Skill* checkSkill(Player* player);
int selectTarget(NowEnemy* enemygroup);
int isEnemyDead(Enemy enemy);
int isEnemyGroupDead(NowEnemy* currentEnemyGroup);
int isPlayerDead(Player* player);
void setEnemyIndex(NowEnemy* currentEnemyGroup);
void battle(Player* player);

// 장착 무기에 따른 변화
// 전역 변수 선언
#define ALL_ENEMY 4
extern Enemy* allEnemy[ALL_ENEMY];

// 장비 extern
extern const Weapon normalSword;
extern const Armor normalArmor;

// 스킬 extern 
extern const Skill Noskill;
extern const Skill Slash;
extern const Skill Agi;
extern const Skill Bufu;
extern const Skill Zio;
extern const Skill Garu;
extern const Skill Megido;
extern const Skill Hama;
extern const Skill Dia;

// 페르소나 extern 
extern Persona orpheus;
extern Persona empty;

// 적 extern 
extern Enemy testEnemy;
extern Enemy shadowSlime;
extern Enemy shadowGoblin;
extern Enemy shadowKnight;