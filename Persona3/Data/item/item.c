#include "item.h"
/*
typedef struct dropItem {
	name itemName[20];
	index itemIndex;
	int price;			//���� �� ����
}DropItem;

typedef struct consumableattackitem {
	name itemName[20];
	index itemIndex;
	int price;			//���� �� ����
	int amount;
	int type;			//��, Ÿ, ��, ȭ, ��, ��, ǳ, ��, ��
}ConsumableAttackItem;

typedef struct consumablehealitem {
	name itemName[20];
	index itemIndex;
	int price;			//���� �� ����
	int amount;
}ConsumableHealItem;	

�򰥸����ʱ����� ����Ǵ°� ���� ������ ������ ����...

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

// ����� 0������� ����
DropItem testdropitem =
{ "�׽�Ʈ ��� ������", 000, 1000 };

// ������ 100������� ����
ConsumableAttackItem testattackitem =
{ "�׽�Ʈ ���� ������", 100, 1000, 100, SLASH };

// ȸ���� 200������� ����
ConsumableHealItem testhealitem =
{ "�׽�Ʈ ȸ�� ������", 200, 1000, 50 };
