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
	NowEnemy currentEnemyGroup;
	printf("---��Ʋ ����!!---\n");
	currentEnemyGroup = makeEnemy();
	while (running)
	{
		ch = '\0';
		str[0] = '\0';
		Persona* currentPersona = &player->personaList.playerPersona[player->personaList.nowPersona];
	// �÷��̾� ��
		printf("[�÷��̾���]");
		printf("\n");
		// �� ���
		for (int i = 0; i < currentEnemyGroup.enemyNum; i++)
		{
			Enemy currentEnemy = currentEnemyGroup.enemyGroup[i];
			printf("���� ��: %s [%d / %d]\n", currentEnemy.enemyName, currentEnemy.enemyStatus.hp, currentEnemy.enemyStatus.hpMax);
		}

		// �޴� ����
		printf("\n~���� ����~\n");
		printf("HP: %d / %d\n", player->playerStatus.hp, player->playerStatus.hpMax);
		printf("MP: %d / %d\n\n", player->playerStatus.mp, player->playerStatus.mpMax);
		printf("�޴��� �����ϼ���...\n1. ��ų\n2. ����\n");
		scanf(" %c", &ch);

		switch (ch) {
		case '1':
			printf("\n���� �丣�ҳ�: %s\n", currentPersona->personaName);
			printf("����� ��ų ����...\n\n");
			for (int i = 0;i < 8;i++) {
				printf("%s	", currentPersona->skillPool[i]->skillName);
				if (i % 2 != 0) {
					printf("\n");
				}
			}
			nowSkill = checkSkill(player);
			useSkill(nowSkill, player, currentPersona, &currentEnemyGroup);

			break;
		case'2':
			printf("���� �������� �ʾҽ��ϴ�...\n");
			break;
		default:
			printf("�߸��� �Է�\n");
			break;
		}

		// �� ��
		printf("\n[�� ��]\n");
		for (int i = 0; i < currentEnemyGroup.enemyNum; i++)
		{
			Enemy* currentEnemy = &currentEnemyGroup.enemyGroup[i];

			// ���� ���� �ൿ �� ��
			if (currentEnemy->enemyStatus.hp <= 0)
			{
				continue;
			}

			printf("\n>> %s�� �ൿ!\n", currentEnemy->enemyName);

			// �ӽ� �⺻ ���� ���� (���� ���� ����)
			int damage = currentEnemy->enemyStatus.stronger + rand() % 10;  // �⺻ ���� + �ణ ���� ������

			printf("%s�� �÷��̾ ����! [%d ������]\n", currentEnemy->enemyName, damage);

			// �÷��̾� HP ���� ����
			player->playerStatus.hp -= damage;
			if (player->playerStatus.hp < 0) player->playerStatus.hp = 0;

			printf("�÷��̾� HP: %d / %d\n", player->playerStatus.hp, player->playerStatus.hpMax);

			// �÷��̾� ��� üũ
			if (player->playerStatus.hp == 0)
			{
				printf("�÷��̾ ��������!\n");
				running = 0;
				break;
			}
		}
	}

















}