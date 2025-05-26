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
   .skillPool = {1, 2, 3, 4, 5, 6, 7, 8}
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

int TcheckSame(char* order, char* personaName)
{
	int len = strlen(order);
	for (int l = 0;l < len;l++) 
	{
		if (order[l] != personaName[l])
		{
			return 0;
		}
	}
	return 1;
}
/*int main(void)
{
	Player player;
	Player* p = &player;
	char ch;

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
			for (int i = 0;i < 8;i++)		// ���� �丣�ҳ� ����
			{
				printf("%s	", player.personaList.playerPersona[i].personaName);
				if (i % 2 != 0)
				{
					printf("\n");
				}
			}
			char* order = (char*)malloc(sizeof(char) * 100);
			scanf("%s", order);		//�丣�ҳ� ���ùޱ�
			for (int i = 0;i < 8;i++)
				if (TcheckSame(order, player.personaList.playerPersona[i].personaName))
				{
					printf("<<���� �丣�ҳ�: %s>>\n", player.personaList.playerPersona[i].personaName);
					printf("<<��� ��ų ����>>\n");
					for (int j = 0;j < 8;j++)	//��ų ����Ʈ ���
					{
						printf("%d	", player.personaList.playerPersona[i].skillPool[j]);
						if (j % 2 != 0)	//�ٹٲ޿�
						{
							printf("\n");
						}
				
					}
					char ch2;
					scanf("%c", &ch2);	//���� �ޱ� ��
					printf("����� ��ų ����: ");
					scanf("%c", &ch2);
					
					//free(order);
					//char* order = (char*)malloc(sizeof(char) * 100);
					// ��ų ��� �Լ� �ۼ��� ��
					/*for (int k = 0;(order + k) != '\0';k++)
					{
						printf("%s", order + k);
					}
					printf("���!\n0");
					break;
					switch (ch2)
					{
						case'1':
							printf("'�Ʊ�' ���!\n\n");
							break;
						case'2':
							printf("'����' ���!\n\n");
							break;
						case'3':
							break;
						case'4':
							break;
						case'5':
							break;
						case'6':
							break;
						case'7':
							break;
						case'8':
							break;
						case'\n':
							printf("���͸� �Է��߾��\n\n");
						default:
							printf("�߸��� �Է�\n");
							break;

					}
				}			
		}
	}
	
}*/
