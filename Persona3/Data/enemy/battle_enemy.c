#include "battle_enemy.h"

/*
typedef struct enemy
{
	char enemyName[20];			// �� �̸�
	int enemyIndex;				// �� �ε���
	int enemyExp;				// ���� ��� ��� ����ġ
	int enemyDropItem[3];		// ���� ��� ���� �� �ִ� ������ ����

	EnemyStatus enemystatus;
}Enemy;
// ���...�����۵� �ٸ� ��ó�� �ε����� �����ϴ°� ���� ������? -> �׷��� �ϱ�� ��
typedef struct enemystatus {	//enemy.h���� ���
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int stronger;
	int intelligence;
	int speed;
	int duration;
	int luck;
	int weekness[9];	//��, Ÿ, ��, ȭ, ��, ��, ǳ, ��, ��
	int buff[3];	    //��, ��, �� ����
	int debuff[3];
}EnemyStatus;
*/

Enemy testShadow =
	{ "�׽�Ʈ ������", 0,					// �̸�, �ε���
	10,									// ��� ����ġ
	{001, 0, 0},							// ��� ������
// �� �������ͽ�...
	{10, 50, 10, 50,					// ü��, ����
	 3, 4, 5, 6, 7,						// �ɷ�ġ
	{0, 0, 0, 0, 0, 0, 0, 0, 0},		// ����
	// ���� ����	
	{0, 0, 0},
	// ����� ����
	{ 0, 0, 0 }}
};
