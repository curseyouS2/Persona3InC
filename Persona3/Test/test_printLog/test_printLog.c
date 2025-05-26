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
   .skillPool = {1, 2, 3, 4, 5, 6, 7, 8}
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
			for (int i = 0;i < 8;i++)		// 소지 페르소나 나열
			{
				printf("%s	", player.personaList.playerPersona[i].personaName);
				if (i % 2 != 0)
				{
					printf("\n");
				}
			}
			char* order = (char*)malloc(sizeof(char) * 100);
			scanf("%s", order);		//페르소나 선택받기
			for (int i = 0;i < 8;i++)
				if (TcheckSame(order, player.personaList.playerPersona[i].personaName))
				{
					printf("<<현재 페르소나: %s>>\n", player.personaList.playerPersona[i].personaName);
					printf("<<사용 스킬 선택>>\n");
					for (int j = 0;j < 8;j++)	//스킬 리스트 출력
					{
						printf("%d	", player.personaList.playerPersona[i].skillPool[j]);
						if (j % 2 != 0)	//줄바꿈용
						{
							printf("\n");
						}
				
					}
					char ch2;
					scanf("%c", &ch2);	//엔터 받기 용
					printf("사용할 스킬 선택: ");
					scanf("%c", &ch2);
					
					//free(order);
					//char* order = (char*)malloc(sizeof(char) * 100);
					// 스킬 사용 함수 작성할 것
					/*for (int k = 0;(order + k) != '\0';k++)
					{
						printf("%s", order + k);
					}
					printf("사용!\n0");
					break;
					switch (ch2)
					{
						case'1':
							printf("'아기' 사용!\n\n");
							break;
						case'2':
							printf("'돌격' 사용!\n\n");
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
							printf("엔터를 입력했어요\n\n");
						default:
							printf("잘못된 입력\n");
							break;

					}
				}			
		}
	}
	
}*/
