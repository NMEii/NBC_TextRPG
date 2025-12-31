#pragma once
#include <random>
using namespace std;

// #include "Random.h" 사용하실 cpp 파일에 추가 후,
// std처럼 Random::Choice(), Random::Success() 형태로 사용
namespace Random {
	static random_device rd;
	static mt19937 mt(rd());

	//min 이상 max 이하의 정수 난수 반환
	inline int Choice(int min, int max) {
		uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

	//percentage 확률로 bool 반환 (ex. 0.3 -> 30% 확률로 true 반환)
	inline bool Success(int percentage) {
		bernoulli_distribution dist(percentage);
		return dist(mt);
	}
}