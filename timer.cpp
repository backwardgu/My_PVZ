#include "timer.h"
Timer::Timer()
{
	last = GetTickCount();
}

//获取计时
DWORD Timer::delta() const
{
	return GetTickCount() - last;
}

// 重置计时器
void Timer::reset() {
	last = GetTickCount();
}

//设置计时器时间
void Timer::set(int time)
{
	last = GetTickCount();
	last -= time;
}