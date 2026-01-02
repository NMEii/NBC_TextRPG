//Buff.cpp
#include "pch.h"
#include "Buff.h"

using namespace std;

BuffInfo::BuffInfo(string inName, BuffType inType, int inValue) :
	name(inName), type(inType), value(inValue)
{
}