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
	printf("---배틀 개시!!---\n");

	while (running)
	{
		ch = '\0';
		str[0] = '\0';
		printf("현재 적: %s\n", testEnemy);
		printf("메뉴를 선택하세요...\n1. 스킬\n2. 공격\n");
		scanf(" %c", &ch);

		switch (ch) {
		case '1':
			printf("현재 페르소나: %s\n", player->personaList.playerPersona[player->personaList.nowPersona].personaName);
			printf("사용할 스킬 선택...\n");
			for (int i = 0;i < 8;i++) {
				printf("%s	", player->personaList.playerPersona[player->personaList.nowPersona].skillPool[i]->skillName);
				if (i % 2 != 0) {
					printf("\n");
				}
			}
			nowSkill = checkSkill(player, str);
			printf("%s 사용!\n", nowSkill->skillName);
			break;
		case'2':
			printf("아직 구현되지 않았습니다...\n");
			break;
		default:
			printf("잘못된 입력\n");
			break;
		}
	}

















}