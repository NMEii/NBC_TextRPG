#pragma once

#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <memory>
#include <limits>
#include <conio.h>
#include <ctime>
#include <unordered_map>
#include <sstream>
#include <map>

struct Pos
{
	int x, y;
};

enum class Key {
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77,
	Enter = 13
};