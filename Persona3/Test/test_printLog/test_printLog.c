#define _CRT_SECURE_NO_WARNINGS
#include "test_printLog.h"
const Persona orpheus = {
   .personaName = "������콺",
   .personaIndex = 1,
   .personaLevel = 1,
   .stronger = 2,
   .intelligence = 2,
   .speed = 2,
   .duration = 2,
   .luck = 2,
   .weekness = {0, 0, 0, 0, 0, 1, 0, 0 ,1},
   .skillPool = {1, 2, 3, 0, 0, 0, 0, 0}
};
const Persona empty = {
	.personaName = "-- �� ���� --",
	.personaIndex = -1,
	.personaLevel = 0,
	.stronger = 0,
	.intelligence = 0,
	.speed = 0,
	.duration = 0,
	.luck = 0,
	.weekness = {0},
	.skillPool = {0}
};
int main(void)
{
	Player player;
	Player* p = &player;
	char ch;
	char order[100];

	int running = 1;
	//initPlayer(p);
	strcpy(p->playerName, "��Ű");
	p->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	//����ü ���ͷ� ����...����ȯ�� �ƴ϶�!!
	p->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty },  // playerPersona �迭
	1,  // numPersona
	0   // nowPersona
	};

	printf("��Ʋ ����!\n");

	while (running) 
	{
		printf("�޴��� �����ϼ���.\n");
		printf("1. �丣�ҳ��� ����\n");
		printf("2. ������ ���\n");
		scanf("%c", &ch);
		switch (ch)
		{
		case '1':
			printf("<<�丣�ҳ��� �����ϼ���...>>\n\n");
			for (int i = 0;i < 8;i++)
			{
				printf("%s	", player.personaList.playerPersona[i].personaName);
				if (i % 2 != 0)
				{
					printf("\n");
				}
			}
			/*scanf("%s", &order);
			for (int i = 0;i < 8;i++)
				if (player.personaList.playerPersona[i].personaName == order)
				{
					printf("<<��� ��ų ����>>");
					//for (int j = 0;j < 8;j++)
					//{
					//	//for (int k = 0;k < 10;k++)
						//{
							//if()
						//}
						//printf("%s", player.personaList.playerPersona[i]);
					//}
				}*/
		}
	}
	
}
