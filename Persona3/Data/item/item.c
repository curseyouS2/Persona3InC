#include "item.h"
/*
typedef struct dropItem {
	name itemName[20];
	index itemIndex;
	int price;			//구매 시 가격
}DropItem;

typedef struct consumableattackitem {
	name itemName[20];
	index itemIndex;
	int price;			//구매 시 가격
	int amount;
	int type;			//참, 타, 관, 화, 빙, 전, 풍, 명, 암
}ConsumableAttackItem;

typedef struct consumablehealitem {
	name itemName[20];
	index itemIndex;
	int price;			//구매 시 가격
	int amount;
}ConsumableHealItem;	

헷갈리지않기위해 공통되는걸 먼저 앞으로 빼도록 하자...

*/
/*	Type
SLASH 0
HIT 1
PENETRATE 2
FIRE 3
ICE 4
ELECTRIC 5
WIND 6
LIGHT 7
NONE 9
*/

// 드랍템 0번대부터 시작
DropItem testdropitem =
{ "테스트 드랍 아이템", 000, 1000 };

// 공격템 100번대부터 시작
ConsumableAttackItem testattackitem =
{ "테스트 공격 아이템", 100, 1000, 100, SLASH };

// 회복템 200번대부터 시작
ConsumableHealItem testhealitem =
{ "테스트 회복 아이템", 200, 1000, 50 };
