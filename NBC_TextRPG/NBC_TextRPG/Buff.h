//Buff.h
#pragma once

enum class BuffType
{
	AttackUp
	//MaxHpUp etc..
};

// Item 사용 함수에서 데이터 생성 및 플레이어 적용
struct BuffInfo
{
	BuffType type;		// 버프 타입
	int value = 0;		// 버프 수치

	BuffInfo(BuffType inType, int inValue);
};