#include "UseSkillTest.h"

int main(void)
{
	Player p;
	Player* player = &p;
	initPlayer(player);

	int running;
	running = 1;
	char ch;
	char str[100];
	Skill* nowSkill;
	printf("---��Ʋ ����!!---\n");

	while (running)
	{
		ch = '\0';
		str[0] = '\0';
		printf("���� ��: %s\n", testEnemy);
		printf("�޴��� �����ϼ���...\n1. ��ų\n2. ����\n");
		scanf(" %c", &ch);

		switch (ch) {
		case '1':
			printf("���� �丣�ҳ�: %s\n", player->personaList.playerPersona[player->personaList.nowPersona].personaName);
			printf("����� ��ų ����...\n");
			for (int i = 0;i < 8;i++) {
				printf("%s	", player->personaList.playerPersona[player->personaList.nowPersona].skillPool[i]->skillName);
				if (i % 2 != 0) {
					printf("\n");
				}
			}
			nowSkill = checkSkill(player, str);
			printf("%s ���!\n", nowSkill->skillName);
			break;
		case'2':
			printf("���� �������� �ʾҽ��ϴ�...\n");
			break;
		default:
			printf("�߸��� �Է�\n");
			break;
		}
	}

















}