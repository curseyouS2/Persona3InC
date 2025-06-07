#include "UseSkillTest.h"
#include <locale.h>

int main(void)
{
	Player p;
	Player* player = &p;
	initPlayer(player);

	int running;
	running = 1;
	char ch;
	char str[100];
	const Skill* nowSkill;
	NowEnemy currentEnemyGroup;
	int playerTurn = 1;
	printf("---배틀 개시!!---\n");
	currentEnemyGroup = makeEnemy();
	while (running)
	{
		ch = '\0';
		str[0] = '\0';
		Persona* currentPersona = &player->personaList.playerPersona[player->personaList.nowPersona];
#pragma region playerturn
		while (playerTurn)
		{
			// 플레이어 턴
			printf("\n---------------------------");
			printf("\n[플레이어턴]\n");
			printf("\n");
			// 적 출력
			for (int i = 0; i < currentEnemyGroup.enemyNum; i++)
			{
				Enemy currentEnemy = currentEnemyGroup.enemyGroup[i];
				printf("현재 적: %s [%d / %d]\n", currentEnemy.enemyName, currentEnemy.enemyStatus.hp, currentEnemy.enemyStatus.hpMax);
			}
			// 메뉴 선택
			printf("\n~현재 상태~\n");
			printf("HP: %d / %d\n", player->playerStatus.hp, player->playerStatus.hpMax);
			printf("MP: %d / %d\n\n", player->playerStatus.mp, player->playerStatus.mpMax);
			printf("메뉴를 선택하세요...\n1. 스킬\n2. 공격\n");
			scanf(" %c", &ch);

			switch (ch) {
			case '1':
				printf("\n현재 페르소나: %s\n", currentPersona->personaName);
				printf("사용할 스킬 선택...\n\n");
				for (int i = 0;i < 8;i++) {
					printf("%s	", currentPersona->skillPool[i]->skillName);
					if (i % 2 != 0) {
						printf("\n");
					}
				}
				nowSkill = checkSkill(player);
				useSkill(nowSkill, player, 1, player, &currentEnemyGroup);
				playerTurn = 0;
				break;
			case'2':
				printf("아직 구현되지 않았습니다...\n");
				break;
			default:
				printf("잘못된 입력\n");
				break;
			}
		}
#pragma endregion
#pragma region enemyturn
		// 적 턴
		printf("\n---------------------------");
		printf("\n[적 턴]\n");
		for (int i = 0; i < currentEnemyGroup.enemyNum; i++)
		{
			Enemy* currentEnemy = &currentEnemyGroup.enemyGroup[i];

			// 죽은 적은 행동 안 함
			if (currentEnemy->enemyStatus.hp <= 0)
			{
				continue;
			}

			printf("\n>> %s의 턴...\n", currentEnemy->enemyName);
			sleep(1000);
			// 임시 기본 공격 구현 (물리 공격 가정)
			int damage = currentEnemy->enemyStatus.stronger + rand() % 10;  // 기본 공격 + 약간 랜덤 데미지

			printf("%s가 플레이어를 공격! [%d 데미지]\n", currentEnemy->enemyName, damage);
			sleep(1000);	//나중에 Sleep 으로 바꿀 것
			// 플레이어 HP 감소 적용
			player->playerStatus.hp -= damage;
			if (player->playerStatus.hp < 0) player->playerStatus.hp = 0;

			printf("플레이어 HP: %d / %d\n", player->playerStatus.hp, player->playerStatus.hpMax);
			sleep(1000);
			// 플레이어 사망 체크
			if (player->playerStatus.hp == 0)
			{
				printf("\n당신은 쓰러졌습니다...\n");
				running = 0;
				break;
			}
		}
		playerTurn = 1;
#pragma endregion
	}

















}