#pragma once
#include "../../Common/common.h"
// �Һ������, ���丮 ������, �� ��� ������ ���� ����ü�� ������ �ұ�??



typedef struct dropItem {
	name itemName[100];
	index itemIndex;
	int price;			//���� �� ���� (�Ǹ��Ҷ��� 0.8 ���Ұ���)
}DropItem;

typedef struct consumableattackitem {
	name itemName[100];
	index itemIndex;
	int type;
	int amount;
	int price;			//���� �� ����
}ConsumableAttackItem;

typedef struct consumablehealitem {
	name itemName[100];
	index itemIndex;
	int amount;
	int price;			//���� �� ����
}ConsumableHealItem;	//�� �Լ� ������? �ۼ��� �Ű����� �޾Ƽ� 