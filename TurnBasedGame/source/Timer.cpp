#include "../header/Timer.h"

Timer::Timer()
{
	ticks = 0;
	started = false;
}

void Timer::start()
{
	started = true;
	ticks = SDL_GetTicks();
}

void Timer::stop()
{
	started = false;
	ticks = 0;
}

void Timer::reset()
{
	ticks = SDL_GetTicks();
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;

	if (started == true)
		time = SDL_GetTicks() - ticks;

	return time;
}


void TimeClock::tick()
{
	minute += speed;
	if (minute >= 60)
	{
		hour++;
		minute -= 60;
		if (hour >= 24)
		{
			hour -= 24;
		}
	}
	if (hour >= 4 && hour < 8) //Night to day
	{
		alpha = maxNight - (((int)(minute)+(hour - 4) * 60) * ((double)maxNight / 240.0));
	}
	else if (hour >= 17 && hour < 21) //Day to night
	{
		alpha = (((int)(minute)+(hour - 17) * 60) * ((double)maxNight / 240.0));
	}
	else if (hour >= 8 && hour < 17) //Daytime
	{
		alpha = maxDay;
	}
	else if (hour >= 21 || hour < 4) //Nighttime
	{
		alpha = maxNight;
	}
	if (alpha >= maxDay && alpha <= maxNight) //Set current max alpha for transitions
	{
		maxAlpha = alpha;
	}
}

string TimeClock::display()
{
	string x = "0";
	string y = "0";
	string xm = "am";
	int hourx = hour;
	if (hourx > 12)
	{
		hourx -= 12;
		xm = "pm";
	}
	if (hourx == 12)
		xm = "pm";
	if (hourx == 0)
		hourx = 12;
	if (hourx >= 10)
		x = "";
	if (minute >= 10)
		y = "";
	return x + to_string(hourx) + ":" + y + to_string((int)minute) + " " + xm;
}