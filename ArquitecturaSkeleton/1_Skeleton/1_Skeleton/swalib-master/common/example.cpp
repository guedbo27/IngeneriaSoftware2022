#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"

#include "Game.h"
#include "Render.h"
#include "Ball.h"

//a
//b
//abcd

float fixedTick = 1.f /60;
LARGE_INTEGER counter;
LARGE_INTEGER frequency;

double previousTime;
double currentTime;
double elapsed;

int count = 0;

double GetTime() 
{
	QueryPerformanceCounter(&counter);
	QueryPerformanceFrequency(&frequency);

	return (double(counter.QuadPart)) / (double(frequency.QuadPart));
}

int Main(void)
{
	Game game;
	Render render;

	render.Inicialize();
	game.Inicialize();

	previousTime = GetTime();

	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{
		currentTime = GetTime();
		elapsed += currentTime - previousTime;
		previousTime = currentTime;

		while (elapsed >= fixedTick) 
		{
			game.Update(fixedTick);
			elapsed = elapsed - fixedTick;
			count++;
		}
		render.Draw(fixedTick);
		SYS_Pump();	// Process Windows messages.
		//SYS_Sleep(17);
	}

	game.Shutdown();
	render.Shutdown();
	return 0;
}