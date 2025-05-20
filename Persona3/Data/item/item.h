#pragma once
#include "../../Common/common.h"
// 소비아이템, 스토리 아이템, 적 드랍 아이템 따로 구조체로 나눠야 할까??



typedef struct dropItem {
	name itemName[100];
	index itemIndex;
	int price;			//구매 시 가격 (판매할때는 0.8 곱할거임)
}DropItem;

typedef struct consumableattackitem {
	name itemName[100];
	index itemIndex;
	int type;
	int amount;
	int price;			//구매 시 가격
}ConsumableAttackItem;

typedef struct consumablehealitem {
	name itemName[100];
	index itemIndex;
	int amount;
	int price;			//구매 시 가격
}ConsumableHealItem;	//힐 함수 포인터? 작성시 매개변수 받아서 