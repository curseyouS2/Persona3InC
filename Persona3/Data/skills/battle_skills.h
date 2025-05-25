#pragma once
#include "../../Common/common.h"

// 스킬 계열
// 물리 공격: 참격, 타격, 관통
// 마법 공격: 화염, 빙결, 전격, 질풍, 빛, 어둠, 무속성
// 회복:
// 스탯 증감:
// 상태이상

typedef struct phycialttack {
	char name[20];
	int skillIndex;
	int damage;
	double cost;		//hpMax에 곱해서 뺄 값 기입
	int type;
	int target;		//단일 타겟 또는 전체 타겟 0이면 단일, 전체면 1
	int accuracy;	//명중 확률
	int times;		//몇 번 때리는 지
}PhysicalAttack;

typedef struct magicattack {
	char name[20];
	int skillIndex;
	int damage;
	int cost;
	int type;
	int target;		//단일 타겟 또는 전체 타겟 0이면 단일, 전체면 1
	int accuracy;	//명중 확률
	int times;		//몇 번 때리는 지
}MagicAttack;

typedef struct immediatedeath {
	char skillname[20];
	int skillIndex;
	int damage;
	int cost;
	int type;
	int target;		//단일 타겟 또는 전체 타겟 0이면 단일, 전체면 1
	int accuracy;	//명중 확률
}ImmediateDeath;

typedef struct heal {
	char skillname[20];
	int skillIndex;
	int amount;
	int cost;
	int target;
}Heal;

// 버프 또는 디버프
// 이름, 인덱스, 단계, 비용, 지속턴
typedef struct buff {	
	char skillname[20];
	int skillIndex;
	int stage;	
	int cost;
	int duration;
}Buff;

typedef Buff DeBuff;

typedef struct doublepower {	// 차지, 컨센트레이트
	char skillname[20];
	int skillIndex;
	int cost;
	int Activate;	//활성화?
}DoublePower;

typedef struct abnormalstatusskill {	// 상태 이상
	char skillname[20];
	int skillIndex;
	int cost;
	int	weirdtype;	//상태이상 타입...
}AbnormalStatus;

//int wholeSkill[100]