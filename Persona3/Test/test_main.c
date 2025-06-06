#include "test_useSkill.h"

int main(void)
{
	Player p; Player* player = &p;
	//Enemy enemy;
	char ch, blank;
	int running = 1;

	strcpy(player->playerName, "유키");
	player->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	//구조체 리터럴 생성...형변환이 아니라!!
	player->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty }, 1, 0 };  // numPersona, nowpersona

	while (running)
	{
		printf("메뉴를 선택하세요.\n");
		printf("1. 페르소나로 공격\n");
		printf("2. 아이템 사용\n");
		scanf("%c", &ch);
		scanf("%c", &blank);
		switch (ch)
		{
			case: '1'
				printf("<<페르소나를 선택하세요...>>\n\n");
				for (int i = 0;i < 8;i++)		// 소지 페르소나 나열
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