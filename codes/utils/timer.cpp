#include "timer.h"
Timer::Timer()
{
	last = GetTickCount();
}
DWORD Timer::delta() const
{
	return GetTickCount() - last;
}

// ÖØÖÃ¼ÆÊ±Æ÷
void Timer::reset() {
	last = GetTickCount();
}
void Timer::set(int time)
{
	last = GetTickCount();
	last -= time;
}