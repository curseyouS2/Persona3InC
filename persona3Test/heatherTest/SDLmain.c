#define SDL_MAIN_HANDLED	// main 내가 작성할거임

#include "game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
// 해상도 1280, 720
// 위치 구조체 배열 (메뉴 선택)
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

int nowSelection = 0; // 스킬 탭부터 시작
// 스킬0 -> 아이템6 으로 가려면... nowSelection = (nowSelection - 1 + 7) % 7
// 한바퀴 돌아도 ㄱㅊ 나머지이기때문에
// 공격1 -> 스킬0 ( 7%7=0이므로 ok

int main(int argc, char* argv[])
{	
	char buffer[256];
	getcwd(buffer, 256);
	printf("현재 실행 경로: %s\n", buffer);

// SDL 초기화..
	if (SDL_Init(SDL_INIT_VIDEO != 0) || SDL_Init(SDL_INIT_AUDIO != 0))
	{
		printf("SDL_Init 에러...%s\n", SDL_GetError());
		// SDL_GetError() : SDL 내부의 가장 최근 오류 메시지를 반환...(문자열임)
		return 1;	// return 1: 비정상 종료...
	}
// SDL_image 초기화 (PNG 출력용 모듈)
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {	//비트연산자 &... 둘다 0이 아닌 값이면 참.
		printf("IMG_Init 에러...%s\n", IMG_GetError());	// 함수 이름 IMG_ ~~
		SDL_Quit();
		return 1;
	}

// SDL_mixer 초기화 (고레벨 오디오 출력, 내부에서 SDL 기본 오디오 함수를 호출하는 방식으로 작동)
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {	//매개변슈: 음질(샘플레이트), 메모리 저장 방식, 채널(모노, 스테레오), 버퍼 크기(속도, cpu부하 영향)
		printf("Mix_OpenAudio 에러...%s\n", Mix_GetError());
		return 1;	
	}

// 창 생성... 
	SDL_Window* window = SDL_CreateWindow(// 매개변수...윈도우(창)이름, 창 생성 x, y 위치, 너비, 높이, 창 속성(flag)
		"persona3InC",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_SHOWN
	);
	if (!window) {	// 위에서 SDL_CreateWindow 실패시 NULL 반환... 그래서 !window
		printf("SDL_CreateWindow 에러...%s\n", SDL_GetError());
		SDL_Quit();	//모든 SDL 종료
		return 1;
	}

// 렌더러 생성...
	// 매개변수...렌더링 대상 윈도우, 렌더링 드라이버 인덱스(-1이 기본), 속성
	// 이번에 들어간 플래그: 하드웨어 가속(속도 향상), 주사율 최적화(수직동기화..)
	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		printf("SDL_CreateRenderer 에러...%s\n", SDL_GetError());
		SDL_DestroyWindow(window);	// 윈도우 파괴
		SDL_Quit();					// SDL 끝
		return 1;					// 비정상 종료
	}

// 나중에 실제로 합칠 때는 서피스/텍스처(포인터) 배열 만들어서 관리할것...ex SurfaceManager, TextureManager...
// 이미지 로딩 (PNG 파일)
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
	// 서피스 오류처리
	if (!SselectBackgroundBig || !SselectBackgroundSmall 
		|| !Smenu0 || !Smenu1 || !Smenu2 || !Smenu3 || !Smenu4 || !Smenu5 || !Smenu6 )
	{
		printf("IMG_Load 에러...%s\n", IMG_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

// 텍스처 생성
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
	
	//서피스 해제
	SDL_FreeSurface(SselectBackgroundBig);  // 서피스는 더 이상 필요 없음(텍스처화 되었기때문에!!)
	SDL_FreeSurface(SselectBackgroundSmall);
	// 텍스처 오류처리
	if (!TselectBackgroundBig || !TselectBackgroundSmall || 
		!Tmenu0 || !Tmenu1 || !Tmenu2 || !Tmenu3 || !Tmenu4 || !Tmenu5 || !Tmenu6 || !Smenu0Selected || !Smenu1Selected || !Smenu2Selected || !Smenu3Selected
		|| !Smenu4Selected || !Smenu5Selected || !Smenu6Selected
		|| !Scommand) {
		printf("SDL_CreateTextureFromSurface 에러...%s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
// 오디오 생성
	Mix_Chunk
		* selectMenu = Mix_LoadWAV("asset/sound/selectMenu.wav"),	// Mix_Chunk: 사운드 데이터 구조체
		* chooseMenu = Mix_LoadWAV("asset/sound/chooseMenu.wav"),
		* changeMenu = Mix_LoadWAV("asset/sound/changeMenu.wav"),
		* exitMenu = Mix_LoadWAV("asset/sound/exitMenu.wav"),
		* battleTheme = Mix_LoadWAV("asset/sound/battleTheme.wav");

	// 오디오 오류처리
	if (!selectMenu) {
		printf("Mix_LoadWAV 에러...%s\n", Mix_GetError());
		return 1;
	}

// 기타
	SDL_Rect bgRect = { 150, 470, 230, 230 };  // 텍스처 위치 / 크기
	SDL_Rect bgRect2 = { 35, 429, 252, 194 }; // 원본 비율 111 82...Command 위치
	SDL_Rect menuSelected = { 157, 555, 60, 60 };
	SDL_Rect menuSelected2 = { 110, 580, 60, 60 };
	SDL_Rect selectCommand = { 39, 453, 252, 194 };
	//SDL_Rect menuPlate = { };


// 본격적인 프로그램 시작...////////////////////////////////////////////////////////////////////////////
		
	double angle = 0.0, angle2 = 0.0;	//각도 초기화...선택 배경 큰 거, 작은 거
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
			// 이벤트, 상태 처리
		while (SDL_PollEvent(&event))	// 메뉴 선택 부분
			{
				if (state == 0) {

					if (event.type == SDL_KEYDOWN)	// 키 누르면
					{
						if (!rotate) // 회전 중에 또 회전하지 않도록... if문 걸어준다
						{
							switch (event.key.keysym.sym)	//만약 그 키가...
							{
							case SDLK_LEFT: case SDLK_UP:	//뒤 원 반시계 회전
								Mix_PlayChannel(-1, changeMenu, 0);
								nowSelection = (nowSelection - 1 + 7) % 7;
								targetAngle = angle - 51.43;
								targetAngle2 = angle2 + 51.43;
								rotate = 1;
								rotatingDirection = -1;
								// 상세 메뉴 회전
								temp = menuSelection[0];
								for (int i = 0; i < 6; i++)
								{
									menuSelection[i] = menuSelection[i + 1];
								}
								menuSelection[6] = temp;

								// 사운드 재생
								Mix_PlayChannel(-1, selectMenu, 0);	//재생 채널, 재생 할 파일, 반복 번 수
								break;
							case SDLK_RIGHT: case SDLK_DOWN: //뒤 원 시계방향 회전
								Mix_PlayChannel(-1, changeMenu, 0);
								nowSelection = (nowSelection + 1) % 7;
								targetAngle = angle + 51.43;	// 메뉴 배경 회전
								targetAngle2 = angle2 - 51.43;
								rotate = 1;
								rotatingDirection = -1;
								temp = menuSelection[6]; // 상세 메뉴 회전
								for (int i = 6; i > 0; i--) {
									menuSelection[i] = menuSelection[i - 1];
								}
								menuSelection[0] = temp;

								// 사운드 재생
								Mix_PlayChannel(-1, selectMenu, 0);	//재생 채널, 재생 할 파일, 반복 번 수
								break;
							case SDLK_SPACE:
								Mix_PlayChannel(-1, chooseMenu, 0);
								state = 1;	// 선택 메뉴 판정으로 전환
								break;
							}
						}
					}
				}
				else if (state == 1)	//선택 후
				{
					if (event.key.keysym.sym == SDLK_BACKSPACE) 
					{
						Mix_PlayChannel(-1, exitMenu, 0);
						state = 0;
					}
						switch (nowSelection) {
						case 0:	// 스킬
							break;
						case 1:
							break;
						}
				}
			// 회전 계산
		}
		if (rotate)	// 아직 angle!=targetAngle이라면!
		{
			double step = 6.0; // 프레임당 이동 각도
			if (angle < targetAngle)
			{
				angle += step;	// targetAngle이 될 때까지 step만큼 더한다..
				angle2 -= step;
				if (angle >= targetAngle)
				{
					angle = targetAngle;	// 위에 코드와 함께 생각해보면 Angle과 targetAngle은 7개 위치의 값만 가지게 됨
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
		// 화면 지우기(초기)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 검정 배경
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, TbackGround, NULL, &(SDL_Rect){0, 0, 1280, 720});
		// 렌더링 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		SDL_RenderCopy(renderer, Tshadow, NULL, &(SDL_Rect){700, 395, 350, 200});
		SDL_RenderCopy(renderer, Tshadow, NULL, &(SDL_Rect){350, 395, 350, 200});
		if (state == 0) // 선택창 렌더링
		{
			SDL_RenderCopyEx(renderer, TselectBackgroundBig, NULL, &bgRect, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, TselectBackgroundSmall, NULL, &bgRect, angle2, NULL, SDL_FLIP_NONE);
			SDL_RenderCopy(renderer, Tcommand, NULL, &bgRect2);
			SDL_RenderCopy(renderer, Tmenu0, NULL, &menuSelection[0]);	//상세 메뉴
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
			case 0: // 스킬
				// 스킬 선택
				//SDL_RenderCopyEx(renderer, TselectCommand, NULL, &selectCommand, commandAngle, &(SDL_Point){-15, 15}, SDL_FLIP_NONE);
				SDL_RenderCopy(renderer, TselectCommand, NULL, &selectCommand);
				SDL_RenderCopy(renderer, TmenuPlate, NULL, &(SDL_Rect){155, 395, 600, 200});
				SDL_RenderCopy(renderer, menu[nowSelection], NULL, &menuSelected2);
				break;
			case 1: // 공격
				//대상 선택
				break;
			case 2: // 도망
				break;
			case 3: // 방어
				break;
			case 4: // 페르소나
				break;
			case 5: // 전략
				break;
			case 6: // 아이템
				break;
			}
		}
		SDL_RenderPresent(renderer);
	}


















// 프로그램 끝...생성된 순서의 역으로 삭제한다.
	Mix_FreeChunk(selectMenu);  // 효과음 해제
	SDL_DestroyTexture(TselectBackgroundBig);
	SDL_DestroyRenderer(renderer);	// 렌더러 해제
	SDL_DestroyWindow(window);		// 윈도우 해제
	IMG_Quit();
	SDL_Quit();	// SDL 모듈(서브시스템)들 종료
}
