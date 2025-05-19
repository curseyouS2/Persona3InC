//스킬 여기다 다 구현함
#include "battle_skills.h"

// 공격 스킬
// 스킬이름, 인덱스, 데미지, 횟수, 비용, 공격타입, 대상, 명중률
// 버프 또는 디버프
// 이름, 인덱스, 단계, 비용, 지속턴

MagicAttack agi 
= { "아기", 1, 5, 1, 3, FIRE, 0, 100 };
PhysicalAttack rush
= { "돌격", 2, 5, 1, 0.07, HIT, 0, 100 };
DeBuff tarunda
= { "타룬다", 3, 1, 6, 3 };