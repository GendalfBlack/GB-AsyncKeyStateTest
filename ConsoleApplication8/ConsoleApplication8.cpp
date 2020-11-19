#include <iostream>
#include <Windows.h>
#include <chrono>
using namespace std;

int main()
{
	auto tp1 = chrono::system_clock::now();					//time variables
	auto tp2 = chrono::system_clock::now();
	
	wchar_t* screen = new wchar_t[120 * 30];				//main screen array
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,  0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //handler for console
	SetConsoleActiveScreenBuffer(hConsole);					//apply handler
	DWORD dwBytesWritten = 0;								//keeps track of stuff
	for (int i = 0; i < 3600; i++)							//to everything in screen
		screen[i] = ' ';									//make empty
	screen[3599] = '\0';									//set last char to end of string for deny scrolling
	
	float x = 10, y = 10;									//character coords
	
	while (1){												//game cycle
		tp2 = chrono::system_clock::now();					//find when is now
		chrono::duration<float> elapsetTime = tp2 - tp1;	//find how much time was from prev frame
		tp1 = tp2;											//remember time
		float deltaTime = elapsetTime.count();				//calculate adjusment for speed of players controls
		
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) //get 'W' keypress
			y -= (10.0f) * deltaTime;						//move up
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) //get 'S' keypress
			y += (10.0f) * deltaTime;						//move up
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000) //get 'A' keypress
			x -= (10.0f) * deltaTime;						//move up
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000) //get 'D' keypress
			x += (10.0f) * deltaTime;						//move up
		
		screen[int(y) * 120 + int(x)] = '.';											//draw character (lives trace of where it was)
		
		swprintf_s(screen, 40, L"FPS=%3.2f WASD for controls", 1.0f / deltaTime);		//show fps and hint
		
		WriteConsoleOutputCharacter(hConsole, screen, 3600, { 0, 0 }, &dwBytesWritten); //update all character on screen
	}
}