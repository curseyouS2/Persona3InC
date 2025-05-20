#include "battle_enemy.h"

/*
typedef struct enemy
{
	char enemyName[20];			// 적 이름
	int enemyIndex;				// 적 인덱스
	int enemyExp;				// 적을 잡고 얻는 경험치
	int enemyDropItem[3];		// 적을 잡고 얻을 수 있는 아이템 종류

	EnemyStatus enemystatus;
}Enemy;
// 고민...아이템도 다른 것처럼 인덱스로 관리하는게 낫지 않을지? -> 그렇게 하기로 함
typedef struct enemystatus {	//enemy.h에서 사용
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int stronger;
	int intelligence;
	int speed;
	int duration;
	int luck;
	int weekness[9];	//참, 타, 관, 화, 빙, 전, 풍, 명, 암
	int buff[3];	    //공, 방, 속 순서
	int debuff[3];
}EnemyStatus;
*/

Enemy testShadow =
	{ "테스트 섀도우", 0,					// 이름, 인덱스
	10,									// 얻는 경험치
	{001, 0, 0},							// 얻는 아이템
// 적 스테이터스...
	{10, 50, 10, 50,					// 체력, 마나
	 3, 4, 5, 6, 7,						// 능력치
	{0, 0, 0, 0, 0, 0, 0, 0, 0},		// 약점
	// 버프 상태	
	{0, 0, 0},
	// 디버프 상태
	{ 0, 0, 0 }}
};
