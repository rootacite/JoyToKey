#pragma once

#include <Windows.h>
typedef struct {
	double x;
	double y;
	UINT   r;
}JoyAram, * LPJoyAram;

#define JOY_EVENT_BUTTONDOWN 0
#define JOY_EVENT_BUTTONUP   1
#define JOY_EVENT_LASMOVE     2
#define JOY_EVENT_TRIGGER    4
#define JOY_EVENT_RASMOVE     8

#define BUTTON_X 0
#define BUTTON_Y 1
#define BUTTON_A 2
#define BUTTON_B 4

#define BUTTON_UP 8
#define BUTTON_DOWN 16
#define BUTTON_LEFT 32
#define BUTTON_RIGHT 64

#define BUTTON_LS 128
#define BUTTON_RS 256

#define BUTTON_LB 512
#define BUTTON_RB 1024

#define BUTTON_P 2048
#define BUTTON_D 4096


#define DLLAPI extern "C" __declspec(dllexport)

typedef void(WINAPI* JOYPROC)(UINT, JoyAram);

DLLAPI void Start();
DLLAPI void Stop();
DLLAPI void SetProc(JOYPROC);