#include "battle_player.h"
/*
// �÷��̾� �丣�ҳ� ���� ����ü
typedef struct playerPersonaList {	
	Persona playerPersona[];
	int numPersona;	//���� �丣�ҳ� ��
	int nowPersona;	//���� ������ �丣�ҳ� 
}PersonaList;

typedef struct playerstatus {	//player.h, aibo.h ���� ���, ���� �ɷ�ġ�� �丣�ҳ��� ���� �޶����Ƿ� ����
	int hpMax;
	int mpMax;
	int hp;
	int mp;
	int buff[3];	//��, ��, ��
	int debuff[3];
}PlayerStatus;

// �÷��̾� ����ü
typedef struct player {
	name playerName[100];
	PlayerStatus playerStatus;
	PersonaList personaList;	// �丣�ҳ� ���� �� ���� �Ҵ�
}Player;

*/
typedef struct player {
	name playerName[100];
	PlayerStatus playerStatus;
	PersonaList personaList;
}Player;

void initPlayer(Player* p)
{
	strcpy(p->playerName, "��Ű");
	p->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	//����ü ���ͷ� ����...����ȯ�� �ƴ϶�!!
	p->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty },  // playerPersona �迭
	1,  // numPersona
	0   // nowPersona
	};
}

int checkTooMuchPersona(Player p)
{
	return p.personaList.numPersona == 8;
}

void getNewPersona(Player p, Persona newpersona)
{
	if (checkTooMuchPersona(p))
	{
		printf("�丣�ҳ��� �ʹ� �����ϴ�...");
	}
	else
	{
		

	}
}


//Player Explayer = {







//}