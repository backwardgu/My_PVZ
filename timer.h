#pragma once
#include "graphics.h"
class Timer
{
public:
	DWORD last = 0;
	Timer();
	DWORD delta()const;
	void reset();
	void set(int time);
};