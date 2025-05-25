#define _CRT_SECURE_NO_WARNINGS
#include "test_printLog.h"
const Persona orpheus = {
   .personaName = "오르페우스",
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
	.personaName = "-- 빈 슬롯 --",
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
	strcpy(p->playerName, "유키");
	p->playerStatus = (PlayerStatus){ 100, 100, 100, 100, {0,0,0}, {0,0,0} };	//구조체 리터럴 생성...형변환이 아니라!!
	p->personaList = (PersonaList){
	{ orpheus, empty, empty, empty, empty, empty, empty, empty },  // playerPersona 배열
	1,  // numPersona
	0   // nowPersona
	};

	printf("배틀 개시!\n");

	while (running) 
	{
		printf("메뉴를 선택하세요.\n");
		printf("1. 페르소나로 공격\n");
		printf("2. 아이템 사용\n");
		scanf("%c", &ch);
		switch (ch)
		{
		case '1':
			printf("<<페르소나를 선택하세요...>>\n\n");
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
					printf("<<사용 스킬 선택>>");
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
