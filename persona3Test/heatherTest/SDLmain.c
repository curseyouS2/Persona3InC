#define SDL_MAIN_HANDLED	// main ���� �ۼ��Ұ���

#include "game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
// �ػ� 1280, 720
// ��ġ ����ü �迭 (�޴� ����)
SDL_Rect menuSelection[7] =
{
	{ 157, 555, 60, 60 },	//0 
	{ 186, 616, 60, 60  },	//1
	{ 254, 631, 60, 60  },	//2
	{ 308, 588, 60, 60  },	//3
	{ 308, 517, 60, 60  },	//4
	{ 254, 477, 60, 60  },	//5
	{ 185, 495, 60, 60  }	//6
};

int nowSelection = 0; // ��ų �Ǻ��� ����
// ��ų0 -> ������6 ���� ������... nowSelection = (nowSelection - 1 + 7) % 7
// �ѹ��� ���Ƶ� ���� �������̱⶧����
// ����1 -> ��ų0 ( 7%7=0�̹Ƿ� ok

int main(int argc, char* argv[])
{	
	char buffer[256];
	getcwd(buffer, 256);
	printf("���� ���� ���: %s\n", buffer);

// SDL �ʱ�ȭ..
	if (SDL_Init(SDL_INIT_VIDEO != 0) || SDL_Init(SDL_INIT_AUDIO != 0))
	{
		printf("SDL_Init ����...%s\n", SDL_GetError());
		// SDL_GetError() : SDL ������ ���� �ֱ� ���� �޽����� ��ȯ...(���ڿ���)
		return 1;	// return 1: ������ ����...
	}
// SDL_image �ʱ�ȭ (PNG ��¿� ���)
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {	//��Ʈ������ &... �Ѵ� 0�� �ƴ� ���̸� ��.
		printf("IMG_Init ����...%s\n", IMG_GetError());	// �Լ� �̸� IMG_ ~~
		SDL_Quit();
		return 1;
	}

// SDL_mixer �ʱ�ȭ (���� ����� ���, ���ο��� SDL �⺻ ����� �Լ��� ȣ���ϴ� ������� �۵�)
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {	//�Ű�����: ����(���÷���Ʈ), �޸� ���� ���, ä��(���, ���׷���), ���� ũ��(�ӵ�, cpu���� ����)
		printf("Mix_OpenAudio ����...%s\n", Mix_GetError());
		return 1;	
	}

// â ����... 
	SDL_Window* window = SDL_CreateWindow(// �Ű�����...������(â)�̸�, â ���� x, y ��ġ, �ʺ�, ����, â �Ӽ�(flag)
		"persona3InC",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_SHOWN
	);
	if (!window) {	// ������ SDL_CreateWindow ���н� NULL ��ȯ... �׷��� !window
		printf("SDL_CreateWindow ����...%s\n", SDL_GetError());
		SDL_Quit();	//��� SDL ����
		return 1;
	}

// ������ ����...
	// �Ű�����...������ ��� ������, ������ ����̹� �ε���(-1�� �⺻), �Ӽ�
	// �̹��� �� �÷���: �ϵ���� ����(�ӵ� ���), �ֻ��� ����ȭ(��������ȭ..)
	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		printf("SDL_CreateRenderer ����...%s\n", SDL_GetError());
		SDL_DestroyWindow(window);	// ������ �ı�
		SDL_Quit();					// SDL ��
		return 1;					// ������ ����
	}

// ���߿� ������ ��ĥ ���� ���ǽ�/�ؽ�ó(������) �迭 ���� �����Ұ�...ex SurfaceManager, TextureManager...
// �̹��� �ε� (PNG ����)
	SDL_Surface
		* SselectBackgroundBig = IMG_Load("asset/selectBackgroundBig.png"),
		* SselectBackgroundSmall = IMG_Load("asset/selectBackgroundSmall.png"),
		* Smenu0 = IMG_Load("asset/menu0.png"),
		* Smenu1 = IMG_Load("asset/menu1.png"),
		* Smenu2 = IMG_Load("asset/menu2.png"),
		* Smenu3 = IMG_Load("asset/menu3.png"),
		* Smenu4 = IMG_Load("asset/menu4.png"),
		* Smenu5 = IMG_Load("asset/menu5.png"),
		* Smenu6 = IMG_Load("asset/menu6.png"),
		* Smenu0Selected = IMG_Load("asset/menu0Selected.png"),
		* Smenu1Selected = IMG_Load("asset/menu1Selected.png"),
		* Smenu2Selected = IMG_Load("asset/menu2Selected.png"),
		* Smenu3Selected = IMG_Load("asset/menu3Selected.png"),
		* Smenu4Selected = IMG_Load("asset/menu4Selected.png"),
		* Smenu5Selected = IMG_Load("asset/menu5Selected.png"),
		* Smenu6Selected = IMG_Load("asset/menu6Selected.png"),
	    * Scommand = IMG_Load("asset/command.png"),
		* SselectCommand = IMG_Load("asset/selectCommand.png"),
		* SmenuPlate = IMG_Load("asset/menuPlate.png"),
		* SmenuDetail = IMG_Load("asset/menuDetail.png"),
		* Sshadow = IMG_Load("asset/shadow.png"),
		* SbackGround = IMG_Load("asset/background.png");
	// ���ǽ� ����ó��
	if (!SselectBackgroundBig || !SselectBackgroundSmall 
		|| !Smenu0 || !Smenu1 || !Smenu2 || !Smenu3 || !Smenu4 || !Smenu5 || !Smenu6 )
	{
		printf("IMG_Load ����...%s\n", IMG_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

// �ؽ�ó ����
	SDL_Texture
		* TselectBackgroundBig = SDL_CreateTextureFromSurface(renderer, SselectBackgroundBig),
		* TselectBackgroundSmall = SDL_CreateTextureFromSurface(renderer, SselectBackgroundSmall),
		* Tmenu0 = SDL_CreateTextureFromSurface(renderer, Smenu0),
		* Tmenu1 = SDL_CreateTextureFromSurface(renderer, Smenu1),
		* Tmenu2 = SDL_CreateTextureFromSurface(renderer, Smenu2),
		* Tmenu3 = SDL_CreateTextureFromSurface(renderer, Smenu3),
		* Tmenu4 = SDL_CreateTextureFromSurface(renderer, Smenu4),
		* Tmenu5 = SDL_CreateTextureFromSurface(renderer, Smenu5),
		* Tmenu6 = SDL_CreateTextureFromSurface(renderer, Smenu6),
		* Tmenu0Selected = SDL_CreateTextureFromSurface(renderer, Smenu0Selected),
		* Tmenu1Selected = SDL_CreateTextureFromSurface(renderer, Smenu1Selected),
		* Tmenu2Selected = SDL_CreateTextureFromSurface(renderer, Smenu2Selected),
		* Tmenu3Selected = SDL_CreateTextureFromSurface(renderer, Smenu3Selected),
		* Tmenu4Selected = SDL_CreateTextureFromSurface(renderer, Smenu4Selected),
		* Tmenu5Selected = SDL_CreateTextureFromSurface(renderer, Smenu5Selected),
		* Tmenu6Selected = SDL_CreateTextureFromSurface(renderer, Smenu6Selected),
		* Tcommand = SDL_CreateTextureFromSurface(renderer, Scommand),
		* TselectCommand = SDL_CreateTextureFromSurface(renderer, SselectCommand),
		* TmenuPlate = SDL_CreateTextureFromSurface(renderer, SmenuPlate),
		* TmenuDetail = SDL_CreateTextureFromSurface(renderer, SmenuDetail),
		* Tshadow = SDL_CreateTextureFromSurface(renderer, Sshadow),
		* TbackGround = SDL_CreateTextureFromSurface(renderer, SbackGround);
	SDL_Texture* menu[7] = {
		Tmenu0Selected, Tmenu1Selected, Tmenu2Selected, Tmenu3Selected, Tmenu4Selected, Tmenu5Selected, Tmenu6Selected };
	
	//���ǽ� ����
	SDL_FreeSurface(SselectBackgroundBig);  // ���ǽ��� �� �̻� �ʿ� ����(�ؽ�óȭ �Ǿ��⶧����!!)
	SDL_FreeSurface(SselectBackgroundSmall);
	// �ؽ�ó ����ó��
	if (!TselectBackgroundBig || !TselectBackgroundSmall || 
		!Tmenu0 || !Tmenu1 || !Tmenu2 || !Tmenu3 || !Tmenu4 || !Tmenu5 || !Tmenu6 || !Smenu0Selected || !Smenu1Selected || !Smenu2Selected || !Smenu3Selected
		|| !Smenu4Selected || !Smenu5Selected || !Smenu6Selected
		|| !Scommand) {
		printf("SDL_CreateTextureFromSurface ����...%s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
// ����� ����
	Mix_Chunk
		* selectMenu = Mix_LoadWAV("asset/sound/selectMenu.wav"),	// Mix_Chunk: ���� ������ ����ü
		* chooseMenu = Mix_LoadWAV("asset/sound/chooseMenu.wav"),
		* changeMenu = Mix_LoadWAV("asset/sound/changeMenu.wav"),
		* exitMenu = Mix_LoadWAV("asset/sound/exitMenu.wav"),
		* battleTheme = Mix_LoadWAV("asset/sound/battleTheme.wav");

	// ����� ����ó��
	if (!selectMenu) {
		printf("Mix_LoadWAV ����...%s\n", Mix_GetError());
		return 1;
	}

// ��Ÿ
	SDL_Rect bgRect = { 150, 470, 230, 230 };  // �ؽ�ó ��ġ / ũ��
	SDL_Rect bgRect2 = { 35, 429, 252, 194 }; // ���� ���� 111 82...Command ��ġ
	SDL_Rect menuSelected = { 157, 555, 60, 60 };
	SDL_Rect menuSelected2 = { 110, 580, 60, 60 };
	SDL_Rect selectCommand = { 39, 453, 252, 194 };
	//SDL_Rect menuPlate = { };


// �������� ���α׷� ����...////////////////////////////////////////////////////////////////////////////
		
	double angle = 0.0, angle2 = 0.0;	//���� �ʱ�ȭ...���� ��� ū ��, ���� ��
	double targetAngle = 0.0, targetAngle2 = 0.0;
	double commandAngle = 300;

	int running = 1;
	int rotate = 0;
	int rotatingDirection = 0;
	SDL_Event event;
	int battle = 1;
	
	int state = 0;
	SDL_Rect temp;
	nowSelection = 0;
	Mix_PlayChannel(-1, battleTheme, 0);
	while (running)
	{
			// �̺�Ʈ, ���� ó��
		while (SDL_PollEvent(&event))	// �޴� ���� �κ�
			{
				if (state == 0) {

					if (event.type == SDL_KEYDOWN)	// Ű ������
					{
						if (!rotate) // ȸ�� �߿� �� ȸ������ �ʵ���... if�� �ɾ��ش�
						{
							switch (event.key.keysym.sym)	//���� �� Ű��...
							{
							case SDLK_LEFT: case SDLK_UP:	//�� �� �ݽð� ȸ��
								Mix_PlayChannel(-1, changeMenu, 0);
								nowSelection = (nowSelection - 1 + 7) % 7;
								targetAngle = angle - 51.43;
								targetAngle2 = angle2 + 51.43;
								rotate = 1;
								rotatingDirection = -1;
								// �� �޴� ȸ��
								temp = menuSelection[0];
								for (int i = 0; i < 6; i++)
								{
									menuSelection[i] = menuSelection[i + 1];
								}
								menuSelection[6] = temp;

								// ���� ���
								Mix_PlayChannel(-1, selectMenu, 0);	//��� ä��, ��� �� ����, �ݺ� �� ��
								break;
							case SDLK_RIGHT: case SDLK_DOWN: //�� �� �ð���� ȸ��
								Mix_PlayChannel(-1, changeMenu, 0);
								nowSelection = (nowSelection + 1) % 7;
								targetAngle = angle + 51.43;	// �޴� ��� ȸ��
								targetAngle2 = angle2 - 51.43;
								rotate = 1;
								rotatingDirection = -1;
								temp = menuSelection[6]; // �� �޴� ȸ��
								for (int i = 6; i > 0; i--) {
									menuSelection[i] = menuSelection[i - 1];
								}
								menuSelection[0] = temp;

								// ���� ���
								Mix_PlayChannel(-1, selectMenu, 0);	//��� ä��, ��� �� ����, �ݺ� �� ��
								break;
							case SDLK_SPACE:
								Mix_PlayChannel(-1, chooseMenu, 0);
								state = 1;	// ���� �޴� �������� ��ȯ
								break;
							}
						}
					}
				}
				else if (state == 1)	//���� ��
				{
					if (event.key.keysym.sym == SDLK_BACKSPACE) 
					{
						Mix_PlayChannel(-1, exitMenu, 0);
						state = 0;
					}
						switch (nowSelection) {
						case 0:	// ��ų
							break;
						case 1:
							break;
						}
				}
			// ȸ�� ���
		}
		if (rotate)	// ���� angle!=targetAngle�̶��!
		{
			double step = 6.0; // �����Ӵ� �̵� ����
			if (angle < targetAngle)
			{
				angle += step;	// targetAngle�� �� ������ step��ŭ ���Ѵ�..
				angle2 -= step;
				if (angle >= targetAngle)
				{
					angle = targetAngle;	// ���� �ڵ�� �Բ� �����غ��� Angle�� targetAngle�� 7�� ��ġ�� ���� ������ ��
					angle2 = targetAngle2;
					rotate = 0;
				}
			}
			else if (angle > targetAngle)
			{
				angle -= step;
				angle2 += step;
				if (angle <= targetAngle)
				{
					angle = targetAngle;
					angle2 = targetAngle2;
					rotate = 0;
				}
			}

			//if()
		}
		// ȭ�� �����(�ʱ�)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // ���� ���
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, TbackGround, NULL, &(SDL_Rect){0, 0, 1280, 720});
		// ������ /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		SDL_RenderCopy(renderer, Tshadow, NULL, &(SDL_Rect){700, 395, 350, 200});
		SDL_RenderCopy(renderer, Tshadow, NULL, &(SDL_Rect){350, 395, 350, 200});
		if (state == 0) // ����â ������
		{
			SDL_RenderCopyEx(renderer, TselectBackgroundBig, NULL, &bgRect, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, TselectBackgroundSmall, NULL, &bgRect, angle2, NULL, SDL_FLIP_NONE);
			SDL_RenderCopy(renderer, Tcommand, NULL, &bgRect2);
			SDL_RenderCopy(renderer, Tmenu0, NULL, &menuSelection[0]);	//�� �޴�
			SDL_RenderCopy(renderer, Tmenu1, NULL, &menuSelection[1]);
			SDL_RenderCopy(renderer, Tmenu2, NULL, &menuSelection[2]);
			SDL_RenderCopy(renderer, Tmenu3, NULL, &menuSelection[3]);
			SDL_RenderCopy(renderer, Tmenu4, NULL, &menuSelection[4]);
			SDL_RenderCopy(renderer, Tmenu5, NULL, &menuSelection[5]);
			SDL_RenderCopy(renderer, Tmenu6, NULL, &menuSelection[6]);
			SDL_RenderCopy(renderer, menu[nowSelection], NULL, &menuSelected);
		}
		else if (state == 1)
		{
			switch (nowSelection)
			{
			case 0: // ��ų
				// ��ų ����
				//SDL_RenderCopyEx(renderer, TselectCommand, NULL, &selectCommand, commandAngle, &(SDL_Point){-15, 15}, SDL_FLIP_NONE);
				SDL_RenderCopy(renderer, TselectCommand, NULL, &selectCommand);
				SDL_RenderCopy(renderer, TmenuPlate, NULL, &(SDL_Rect){155, 395, 600, 200});
				SDL_RenderCopy(renderer, menu[nowSelection], NULL, &menuSelected2);
				break;
			case 1: // ����
				//��� ����
				break;
			case 2: // ����
				break;
			case 3: // ���
				break;
			case 4: // �丣�ҳ�
				break;
			case 5: // ����
				break;
			case 6: // ������
				break;
			}
		}
		SDL_RenderPresent(renderer);
	}


















// ���α׷� ��...������ ������ ������ �����Ѵ�.
	Mix_FreeChunk(selectMenu);  // ȿ���� ����
	SDL_DestroyTexture(TselectBackgroundBig);
	SDL_DestroyRenderer(renderer);	// ������ ����
	SDL_DestroyWindow(window);		// ������ ����
	IMG_Quit();
	SDL_Quit();	// SDL ���(����ý���)�� ����
}
