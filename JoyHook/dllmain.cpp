// dllmain.cpp : Defines the entry point for the DLL application.


#include "pch.h"


#include "JoyHook.h"
#include <iostream> 


using namespace std;
#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>
JOYPROC Proc = NULL;

bool Hooking = false;

bool X = false, Y = false, A = false, B = false;
bool LB = false, RB = false, Plus = false, Devide = false, LS = false, RS = false;

double T = 0;
double Lx = 0, Ly = 0;
double Rx = 0, Ry = 0;

int Toward = 0;

DLLAPI void Start()
{
    Hooking = true;
}
DLLAPI void Stop()
{
    Hooking = false;
}
DLLAPI void SetProc(JOYPROC nProc)
{
    Proc = nProc;
}

DWORD WINAPI Thread(LPVOID Param) 
{
	JOYINFOEX* nx = new JOYINFOEX;

	while (1) {
		if (!Hooking) {
			Sleep(1);
			continue;
		}
		nx->dwFlags = JOY_RETURNALL;
		MMRESULT r = joyGetPosEx(JOYSTICKID1, nx);
		if (r == JOYERR_NOERROR)
		{
			bool OldA = A, OldB = B, OldX = X, OldY = Y, OldLB = LB, OldRB = RB, OldLS = LS, OldRS = RS, OldPlus = Plus, OldDevide = Devide;
			int OldToward = Toward;
			double OldLx = Lx, OldLy = Ly, OldRx = Rx, OldRy = Ry, OldT = T;

			A = ((nx->dwButtons & 1) != 0);
			B = ((nx->dwButtons & 2) != 0);
			X = ((nx->dwButtons & 4) != 0);
			Y = ((nx->dwButtons & 8) != 0);

			LB = ((nx->dwButtons & 16) != 0);
			RB = ((nx->dwButtons & 32) != 0);
			LS = ((nx->dwButtons & 256) != 0);
			RS = ((nx->dwButtons & 512) != 0);

			Plus = ((nx->dwButtons & 128) != 0);
			Devide = ((nx->dwButtons & 64) != 0);

			switch (nx->dwPOV) {
			case 0xffff:
				Toward = 0;
				break;
			case 0:
				Toward = 1;
				break;
			case 0x6978:
				Toward = 2;
				break;
			case 0x4650:
				Toward = 3;
				break;
			case 0x2328:
				Toward = 4;
				break;
			}

			Lx = (((int)nx->dwXpos - 32767) / (double)32767);
			Ly = (((int)nx->dwYpos - 32767) / (double)32767);

			Rx = (((int)nx->dwUpos - 32767) / (double)32767);
			Ry = (((int)nx->dwRpos - 32767) / (double)32767);

			T = (((int)nx->dwZpos - 32767) / (double)32767);

			if (Proc == NULL) {
				Sleep(1);
				continue;
			}

			
			if (OldA != A) {
				if (A)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_A });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_A });
			}
			if (OldB != B) {
				if (B)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_B });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_B });
			}
			if (OldX != X) {
				if (X)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_X });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_X });
			}
			if (OldY != Y) {
				if (Y)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_Y });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_Y });
			}

			if (OldLB != LB) {
				if (LB)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_LB });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_LB });
			}
			if (OldRB != RB) {
				if (RB)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_RB });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_RB });
			}
			if (OldLS != LS) {
				if (LS)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_LS });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_LS });
			}
			if (OldRS != RS) {
				if (RS)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_RS });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_RS });
			}

			if (OldPlus != Plus){
				if (Plus)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_P });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_P });
			}
			if (OldDevide != Devide) {
				if (Devide)Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_D });
				else Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_D });
			}

			if (Toward != OldToward) {
				if (Toward == 0)
				{
					switch (OldToward) {
					case 1:
						Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_UP });
						break;
					case 2:
						Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_LEFT });
						break;
					case 3:
						Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_DOWN });
						break;
					case 4:
						Proc(JOY_EVENT_BUTTONUP, { 0,0,BUTTON_RIGHT });
						break;
					}
				}
				else {
					switch (Toward) {
					case 1:
						Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_UP });
						break;
					case 2:
						Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_LEFT });
						break;
					case 3:
						Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_DOWN });
						break;
					case 4:
						Proc(JOY_EVENT_BUTTONDOWN, { 0,0,BUTTON_RIGHT });
						break;
					}
				}
			}


			if (OldLx != Lx || OldLy != Ly) {
				Proc(JOY_EVENT_LASMOVE, { Lx,Ly,0 });
			}
			if (OldRx != Rx || OldRy != Ry) {
				Proc(JOY_EVENT_RASMOVE, { Rx,Ry,0 });
			}

			if (OldT != T ) {
				Proc(JOY_EVENT_TRIGGER, { T,0,0 });
			}
		}
		else
		{
			//MessageBox(0, L"Error", L"Error", MB_ICONERROR);
			return 0;
		}
		Sleep(1);
	}
	return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, Thread, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

