#include "timer.h"
Timer::Timer()
{
	last = GetTickCount();
}
DWORD Timer::delta()
{
	DWORD now = GetTickCount();
	DWORD interval = now - last;
	return interval;
}
DWORD Timer::last_reset() const
{
	return GetTickCount() - last;
}

// ÷ÿ÷√º∆ ±∆˜
void Timer::reset() {
	last = GetTickCount();
}