#include "test_useSkill.h"

int main(void)
{
	Player p; Player* player = &p;
	//Enemy enemy;
	char ch, blank;
	int running = 1;

	strcpy(player->playerName, "��Ű");
	player->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	//����ü ���ͷ� ����...����ȯ�� �ƴ϶�!!
	player->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty }, 1, 0 };  // numPersona, nowpersona

	while (running)
	{
		printf("�޴��� �����ϼ���.\n");
		printf("1. �丣�ҳ��� ����\n");
		printf("2. ������ ���\n");
		scanf("%c", &ch);
		scanf("%c", &blank);
		switch (ch)
		{
			case: '1'
				printf("<<�丣�ҳ��� �����ϼ���...>>\n\n");
				for (int i = 0;i < 8;i++)		// ���� �丣�ҳ� ����
				{
					printf("%s	", player->personaList[i].personaName);
					if (i % 2 != 0)
					{
						printf("\n");
					}
				}
		}


	}




}