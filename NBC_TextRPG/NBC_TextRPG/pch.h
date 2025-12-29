#pragma once

#include <vector>
#include <string>
#include <windows.h>
#include <memory>
#include <conio.h>
#include <ctime>
#include <unordered_map>

#define UP 72
#define DOWN 80
#define RIGHT 77 
#define LEFT 75
#define ESCAPE 27 


struct Pos
{
	int x, y;
};