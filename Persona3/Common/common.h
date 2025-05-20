#ifndef COMMON_H	//common.h 정의되어있지 않다면 
# define COMMON_H	//정의하세요
// if절 구분을 위해 들여쓰기를 해주자
// include할 다른 헤더 파일 명시

# include<stdio.h>
# include<time.h>
# include<stdlib.h>
# include<string.h>

// 매크로 정의
	// 공격, 약점 타입
# define SLASH 0
# define HIT 1
# define PENETRATE 2
# define FIRE 3
# define ICE 4
# define ELECTRIC 5
# define WIND 6
# define LIGHT 7
# define DARK 8
# define NONE 9

// 사용자 struct, type 정의
 typedef char name;
 typedef int index;	// 나중에 index의 int 모두 index로 바꿀 것...
 typedef int level;
 typedef int stat;




// 전역변수 선언

// 함수 선언

#endif //정의 끝