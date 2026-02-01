#pragma once
#include <graphics.h>
class Timer
{
public:
	DWORD last = 0;
	Timer();
	DWORD delta();
	DWORD last_reset()const;
	void reset();
};