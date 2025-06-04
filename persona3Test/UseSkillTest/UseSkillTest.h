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


// 사용자 struct, type 정의
typedef char name;
typedef int index;	// 나중에 index의 int 모두 index로 바꿀 것...
typedef int level;
typedef int stat;

// 필요 경험치 배열 [0]: 1 -> 2
int nextLevelExp[9] = {
	7, 21, 63, 189, 577, 1721, 2523, 3750, 5102
};
typedef struct Level {
	level nowLevel;
	int nowExp;	//nowExp >= nextLevelExp[nowLevel-1] -> 레벨업
}Level;
// 스킬 정의

typedef struct phycialttack {
	double cost;
	int amount;
	int times;	 // 번 수
	int target;
	int accuracy;
	int property; // 스킬 속성
}PhysicalAttack;
typedef struct magicattack {
	int cost;
	int amount;
	int times;	 // 번 수
	int target;
	int accuracy;
	int property; // 스킬 속성
}MagicAttack;
typedef struct immediatedeath {
	int cost;
	int amount;
	int times;	 // 번 수
	int target;
	int accuracy;
	int property; // 스킬 속성
}ImmediateDeath;
typedef struct heal {
	int cost;
	int amount;
	int times;	 // 번 수
	int target;
	int accuracy;
	int property; // 스킬 속성
}Heal;
typedef struct buff {
	int cost;
	int bufftype; //0, 1, 2 공, 방, 속
	int target;	  //적군, 적군 전체, 아군, 아군 전체 0, 1, 2, 3
}Buff;
typedef Buff DeBuff;
typedef struct doublepower {	// 차지, 컨센트레이트
	int Activate;	//활성화?
}DoublePower;
typedef struct abnormalstatusskill {	// 상태 이상
	int cost;
	int target;
	int accuracy;
	int	weirdtype;	//상태이상 타입...
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

// 페르소나 정의
typedef struct persona {
	// 이름, 인덱스, 공, 마, 속, 내, 운, 내성, 스킬풀
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

// 플레이어 정의
typedef struct playerstatus {	//player.h, aibo.h 에서 사용, 세부 능력치는 페르소나에 따라 달라지므로 뺐음
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int buff[3];	//공, 방, 속
	int debuff[3];
	int physicdouble; int magicdouble;
}PlayerStatus;
typedef struct playerPersonaList {
	Persona playerPersona[8];
	int numPersona;	//현재 페르소나 수
	int nowPersona;	//현재 장착한 페르소나 
}PersonaList;
typedef struct player {
	name playerName[100];
	Level playerLevel;
	PlayerStatus playerStatus;
	PersonaList personaList;	
}Player;

// 적 정의
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
	int buff[3];	//공, 방, 속
	int debuff[3];
}EnemyStatus;
typedef struct enemy{
	name enemyName[20];			// 적 이름
	index enemyIndex;			// 적 인덱스	
	EnemyStatus enemyStatus;
	int enemyExp;				// 획득 경험치
	int enemyDropItem[3];		// 드롭 아이템
}Enemy;

// 함수 모음
void initPlayer(Player* player);

int physicDouble(Player* player);
int magicDouble(Player* player);
int calcDamage(Skill* skill, Player* player, int amount, stat bonus);
void attack(int damage, Enemy* enemy);
void heal(Skill* skill, Player* player);
int imDeath(Skill* skill, Player* player, Enemy* enemy);
void useSkill(Skill* skill, Player* player, Persona* persona, Enemy* enemy);

// 페르소나 구현
Persona orpheus;
Persona empty;