#include "stdafx.h"

//
// Constants for gamepad buttons
//
#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000


#define POINTERSPEED						7			//Speed of mouse pointer reiteration. Do not edit
#define POINTERDIST							3			//Distance moved by mouse pointer
#define POINTERDISTADD						22			//Increase distance moved of mouse pointer by how much

#define BUTTONDELAY							200			//Gamepad button delay
#define MOVEMENTDELAY						15			//Gamepad button delay


static HANDLE XinputThread;

static CXBOXController* Player1;

static BOOL releasedLClick = TRUE;
static BOOL releasedRClick = TRUE;
static BOOL releasedAlt = TRUE;
static BOOL releasedShift = TRUE;

static BOOL releasedW = TRUE;
static BOOL releasedS = TRUE;
static BOOL releasedA = TRUE;
static BOOL releasedD = TRUE;

static BOOL releasedUp = TRUE;
static BOOL releasedDown = TRUE;
static BOOL releasedRight = TRUE;
static BOOL releasedLeft = TRUE;

static BOOL releasedShift2 = TRUE;

static BOOL releasedSpace = TRUE;
static BOOL releasedX = TRUE;

static bool XinputLoaded = false;
static bool XinputNotice = false;

BOOL STDCALL Threads(LPVOID Parameter)
{
	INT Thread = (INT)Parameter;

	switch (Thread)
	{
	case XINPUT:
		while (true)
		{
			Sleep(10);

			if (!XinputLoaded)
			{
				Player1 = new CXBOXController(1);

				if (Player1->IsConnected())
				{
					XinputLoaded = TRUE;
					XinputNotice = FALSE;
				}
			}

			if (Player1->IsConnected())
			{
				POINT p = { 0 };
				GetCursorPos(&p);

				SHORT PointerTravel = POINTERDIST;

				//Joy 1
				float rightThumbX = Player1->GetState().Gamepad.sThumbRX;
				float rightThumbY = Player1->GetState().Gamepad.sThumbRY;

				//Joy 2
				float leftThumbX = Player1->GetState().Gamepad.sThumbLX;
				float leftThumbY = Player1->GetState().Gamepad.sThumbLY;

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				{
					INPUT Inputs2[1] = { 0 };

					// Set up a generic keyboard event.
					Inputs2[0].type = INPUT_KEYBOARD;
					Inputs2[0].ki.wScan = 0; // hardware scan code for key
					Inputs2[0].ki.time = 0;
					Inputs2[0].ki.dwExtraInfo = 0;

					// Release the "Shift" key
					Inputs2[0].ki.wVk = 16; // virtual-key code for the "Shift" key
					Inputs2[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(1, Inputs2, sizeof(INPUT));

					Sleep(MOVEMENTDELAY);

					INPUT Inputs[1] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "Space" key
					Inputs[0].ki.wVk = 32; // virtual-key code for the "Space" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					SendInput(1, Inputs, sizeof(INPUT));

					Sleep(MOVEMENTDELAY);

					releasedSpace = FALSE;

					continue;
				}
				else
				{
					if (releasedSpace == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						// Complete a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Release the "Space" key
						Inputs[0].ki.wVk = 32; // virtual-key code for the "Space" key
						Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedSpace = TRUE;

						continue;
					}
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
				{
					INPUT Inputs[1] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "X" key
					Inputs[0].ki.wVk = 88; // virtual-key code for the "X" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					SendInput(1, Inputs, sizeof(INPUT));

					Sleep(MOVEMENTDELAY);

					releasedX = FALSE;

					continue;
				}
				else
				{
					if (releasedX == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						// Complete a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Release the "X" key
						Inputs[0].ki.wVk = 88; // virtual-key code for the "X" key
						Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedX = TRUE;

						continue;
					}
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				{
					//Z
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "Z" key
					Inputs[0].ki.wVk = 90; // virtual-key code for the "Z" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "Z" key
					Inputs[1].ki.wVk = 90; // virtual-key code for the "Z" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && rightThumbX < -16384)
				{
					//V
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "V" key
					Inputs[0].ki.wVk = 86; // virtual-key code for the "V" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "V" key
					Inputs[1].ki.wVk = 86; // virtual-key code for the "V" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && rightThumbX > 16383)
				{
					//Slash
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "Slash" key
					Inputs[0].ki.wVk = 111; // virtual-key code for the "Slash" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "Slash" key
					Inputs[1].ki.wVk = 111; // virtual-key code for the "Slash" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
				{
					//Esc
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "Esc" key
					Inputs[0].ki.wVk = 27; // virtual-key code for the "Esc" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "Esc" key
					Inputs[1].ki.wVk = 27; // virtual-key code for the "Esc" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				{
					//Shift + B
					INPUT Inputs[4] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "Shift" key
					Inputs[0].ki.wVk = 16; // virtual-key code for the "Shift" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Set up a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Press the "B" key
					Inputs[1].ki.wVk = 66; // virtual-key code for the "B" key
					Inputs[1].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[2].type = INPUT_KEYBOARD;
					Inputs[2].ki.wScan = 0; // hardware scan code for key
					Inputs[2].ki.time = 0;
					Inputs[2].ki.dwExtraInfo = 0;

					// Release the "Shift" key
					Inputs[2].ki.wVk = 16; // virtual-key code for the "Shift" key
					Inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[3].type = INPUT_KEYBOARD;
					Inputs[3].ki.wScan = 0; // hardware scan code for key
					Inputs[3].ki.time = 0;
					Inputs[3].ki.dwExtraInfo = 0;

					// Release the "B" key
					Inputs[3].ki.wVk = 66; // virtual-key code for the "B" key
					Inputs[3].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(4, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
				{
					//L
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "L" key
					Inputs[0].ki.wVk = 76; // virtual-key code for the "L" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "L" key
					Inputs[1].ki.wVk = 76; // virtual-key code for the "L" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
				{
					//M
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "M" key
					Inputs[0].ki.wVk = 77; // virtual-key code for the "M" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "M" key
					Inputs[1].ki.wVk = 77; // virtual-key code for the "M" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && leftThumbY > 16383)
				{
					//C
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "C" key
					Inputs[0].ki.wVk = 67; // virtual-key code for the "C" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "C" key
					Inputs[1].ki.wVk = 67; // virtual-key code for the "C" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && leftThumbX > 16383)
				{
					//P
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "P" key
					Inputs[0].ki.wVk = 80; // virtual-key code for the "P" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "P" key
					Inputs[1].ki.wVk = 80; // virtual-key code for the "P" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && leftThumbY < -16384)
				{
					//N
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "N" key
					Inputs[0].ki.wVk = 78; // virtual-key code for the "N" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "N" key
					Inputs[1].ki.wVk = 78; // virtual-key code for the "N" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && leftThumbX < -16384)
				{
					//Y
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "Y" key
					Inputs[0].ki.wVk = 89; // virtual-key code for the "Y" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "Y" key
					Inputs[1].ki.wVk = 89; // virtual-key code for the "Y" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && rightThumbY > 16383)
				{
					//F3
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "F3" key
					Inputs[0].ki.wVk = 114; // virtual-key code for the "F3" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "F3" key
					Inputs[1].ki.wVk = 114; // virtual-key code for the "F3" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && rightThumbY < -16384)
				{
					//F4
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "F4" key
					Inputs[0].ki.wVk = 115; // virtual-key code for the "F4" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "F4" key
					Inputs[1].ki.wVk = 115; // virtual-key code for the "F4" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				else
				{
				}
				
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
				{
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP || Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN || Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT || Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
					{
						INPUT Inputs[2] = { 0 };

						// Set up a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Press the "Space" key
						Inputs[0].ki.wVk = 32; // virtual-key code for the "Space" key
						Inputs[0].ki.dwFlags = 0; // 0 for key press

						Sleep(BUTTONDELAY);

						// Complete a generic keyboard event.
						Inputs[1].type = INPUT_KEYBOARD;
						Inputs[1].ki.wScan = 0; // hardware scan code for key
						Inputs[1].ki.time = 0;
						Inputs[1].ki.dwExtraInfo = 0;

						// Release the "Space" key
						Inputs[1].ki.wVk = 32; // virtual-key code for the "Space" key
						Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
						SendInput(2, Inputs, sizeof(INPUT));

						continue;
					}

					INPUT Inputs[1] = { 0 };

					Inputs[0].type = INPUT_MOUSE;
					Inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

					SendInput(1, Inputs, sizeof(INPUT));

					releasedRClick = FALSE;
				}
				else
				{
					if (releasedRClick == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						Inputs[0].type = INPUT_MOUSE;
						Inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

						SendInput(1, Inputs, sizeof(INPUT));

						releasedRClick = TRUE;
					}
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
				{
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
					{
						INPUT Inputs[1] = { 0 };

						// Set up a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Press the "Up-Arrow" key
						Inputs[0].ki.wVk = 38; // virtual-key code for the "Up-Arrow" key
						Inputs[0].ki.dwFlags = 0; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedUp = FALSE;
					}
					else
					{
						if (releasedUp == FALSE)
						{
							INPUT Inputs[1] = { 0 };

							// Complete a generic keyboard event.
							Inputs[0].type = INPUT_KEYBOARD;
							Inputs[0].ki.wScan = 0; // hardware scan code for key
							Inputs[0].ki.time = 0;
							Inputs[0].ki.dwExtraInfo = 0;

							// Release the "Up-Arrow" key
							Inputs[0].ki.wVk = 38; // virtual-key code for the "Up-Arrow" key
							Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

							SendInput(1, Inputs, sizeof(INPUT));

							releasedUp = TRUE;
						}
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
					{
						INPUT Inputs[1] = { 0 };

						// Set up a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Press the "Down-Arrow" key
						Inputs[0].ki.wVk = 40; // virtual-key code for the "Down-Arrow" key
						Inputs[0].ki.dwFlags = 0; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedDown = FALSE;
					}
					else
					{
						if (releasedDown == FALSE)
						{
							INPUT Inputs[1] = { 0 };

							// Complete a generic keyboard event.
							Inputs[0].type = INPUT_KEYBOARD;
							Inputs[0].ki.wScan = 0; // hardware scan code for key
							Inputs[0].ki.time = 0;
							Inputs[0].ki.dwExtraInfo = 0;

							// Release the "Down-Arrow" key
							Inputs[0].ki.wVk = 40; // virtual-key code for the "Down-Arrow" key
							Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

							SendInput(1, Inputs, sizeof(INPUT));

							releasedDown = TRUE;
						}
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
					{
						INPUT Inputs[1] = { 0 };

						// Set up a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Press the "Left-Arrow" key
						Inputs[0].ki.wVk = 37; // virtual-key code for the "Left-Arrow" key
						Inputs[0].ki.dwFlags = 0; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedLeft = FALSE;
					}
					else
					{
						if (releasedLeft == FALSE)
						{
							INPUT Inputs[1] = { 0 };

							// Complete a generic keyboard event.
							Inputs[0].type = INPUT_KEYBOARD;
							Inputs[0].ki.wScan = 0; // hardware scan code for key
							Inputs[0].ki.time = 0;
							Inputs[0].ki.dwExtraInfo = 0;

							// Release the "Left-Arrow" key
							Inputs[0].ki.wVk = 37; // virtual-key code for the "Left-Arrow" key
							Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

							SendInput(1, Inputs, sizeof(INPUT));

							releasedLeft = TRUE;
						}
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
					{
						INPUT Inputs[1] = { 0 };

						// Set up a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Press the "Right-Arrow" key
						Inputs[0].ki.wVk = 39; // virtual-key code for the "Right-Arrow" key
						Inputs[0].ki.dwFlags = 0; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedRight = FALSE;
					}
					else
					{
						if (releasedRight == FALSE)
						{
							INPUT Inputs[1] = { 0 };

							// Complete a generic keyboard event.
							Inputs[0].type = INPUT_KEYBOARD;
							Inputs[0].ki.wScan = 0; // hardware scan code for key
							Inputs[0].ki.time = 0;
							Inputs[0].ki.dwExtraInfo = 0;

							// Release the "Right-Arrow" key
							Inputs[0].ki.wVk = 39; // virtual-key code for the "Right-Arrow" key
							Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

							SendInput(1, Inputs, sizeof(INPUT));

							releasedRight = TRUE;
						}
					}
					continue;
				}

				if (leftThumbY > 16383)
				{
					//1
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "1" key
					Inputs[0].ki.wVk = 49; // virtual-key code for the "1" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "1" key
					Inputs[1].ki.wVk = 49; // virtual-key code for the "1" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				if (leftThumbX > 16383)
				{
					//2
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "2" key
					Inputs[0].ki.wVk = 50; // virtual-key code for the "2" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "2" key
					Inputs[1].ki.wVk = 50; // virtual-key code for the "2" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				if (leftThumbY < -16384)
				{
					//3
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "3" key
					Inputs[0].ki.wVk = 51; // virtual-key code for the "3" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "3" key
					Inputs[1].ki.wVk = 51; // virtual-key code for the "3" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				if (leftThumbX < -16384)
				{
					//4
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "4" key
					Inputs[0].ki.wVk = 52; // virtual-key code for the "4" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "4" key
					Inputs[1].ki.wVk = 52; // virtual-key code for the "4" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				if (rightThumbY > 16383)
				{
					//5
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "5" key
					Inputs[0].ki.wVk = 53; // virtual-key code for the "5" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "5" key
					Inputs[1].ki.wVk = 53; // virtual-key code for the "5" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				if (rightThumbX > 16383)
				{
					//6
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "6" key
					Inputs[0].ki.wVk = 54; // virtual-key code for the "6" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "6" key
					Inputs[1].ki.wVk = 54; // virtual-key code for the "6" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				if (rightThumbY < -16384)
				{
					//7
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "7" key
					Inputs[0].ki.wVk = 55; // virtual-key code for the "7" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "7" key
					Inputs[1].ki.wVk = 55; // virtual-key code for the "7" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}
				if (rightThumbX < -16384)
				{
					//8
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "8" key
					Inputs[0].ki.wVk = 56; // virtual-key code for the "8" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "8" key
					Inputs[1].ki.wVk = 56; // virtual-key code for the "8" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
				{
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "-" key
					Inputs[0].ki.wVk = 189; // virtual-key code for the "-" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "-" key
					Inputs[1].ki.wVk = 189; // virtual-key code for the "-" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
				{
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "=" key
					Inputs[0].ki.wVk = 187; // virtual-key code for the "=" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "=" key
					Inputs[1].ki.wVk = 187; // virtual-key code for the "=" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				{
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "9" key
					Inputs[0].ki.wVk = 57; // virtual-key code for the "9" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "9" key
					Inputs[1].ki.wVk = 57; // virtual-key code for the "9" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
				{
					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "0" key
					Inputs[0].ki.wVk = 48; // virtual-key code for the "0" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "0" key
					Inputs[1].ki.wVk = 48; // virtual-key code for the "0" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					continue;
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				{
					INPUT Inputs[1] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "Shift" key
					Inputs[0].ki.wVk = 16; // virtual-key code for the "Shift" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					SendInput(1, Inputs, sizeof(INPUT));

					releasedShift2 = FALSE;
				}
				else
				{
					if (releasedShift2 == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						// Complete a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Release the "Shift" key
						Inputs[0].ki.wVk = 16; // virtual-key code for the "Shift" key
						Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedShift2 = TRUE;
					}
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					PointerTravel = POINTERDISTADD;

					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					{
						PointerTravel = POINTERDIST;
					}

					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
					{
						SetCursorPos(p.x - PointerTravel, p.y - PointerTravel);

						SleepEx(POINTERSPEED, TRUE);

						continue;
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
					{
						SetCursorPos(p.x + PointerTravel, p.y - PointerTravel);

						SleepEx(POINTERSPEED, TRUE);

						continue;
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
					{
						SetCursorPos(p.x - PointerTravel, p.y + PointerTravel);

						SleepEx(POINTERSPEED, TRUE);

						continue;
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
					{
						SetCursorPos(p.x + PointerTravel, p.y + PointerTravel);

						SleepEx(POINTERSPEED, TRUE);

						continue;
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
					{
						SetCursorPos(p.x, p.y - PointerTravel);

						SleepEx(POINTERSPEED, TRUE);

						continue;
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
					{
						SetCursorPos(p.x, p.y + PointerTravel);

						SleepEx(POINTERSPEED, TRUE);

						continue;
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
					{
						SetCursorPos(p.x - PointerTravel, p.y);

						SleepEx(POINTERSPEED, TRUE);

						continue;
					}
					if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
					{
						SetCursorPos(p.x + PointerTravel, p.y);

						SleepEx(POINTERSPEED, TRUE);

						continue;
					}
				}
				
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
				{
					INPUT Inputs[1] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "W" key
					Inputs[0].ki.wVk = 87; // virtual-key code for the "W" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					SendInput(1, Inputs, sizeof(INPUT));

					Sleep(MOVEMENTDELAY);

					releasedW = FALSE;
				}
				else
				{
					if (releasedW == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						// Complete a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Release the "W" key
						Inputs[0].ki.wVk = 87; // virtual-key code for the "W" key
						Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedW = TRUE;
					}
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
				{
					INPUT Inputs[1] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "S" key
					Inputs[0].ki.wVk = 83; // virtual-key code for the "S" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					SendInput(1, Inputs, sizeof(INPUT));

					Sleep(MOVEMENTDELAY);

					releasedS = FALSE;
				}
				else
				{
					if (releasedS == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						// Complete a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Release the "S" key
						Inputs[0].ki.wVk = 83; // virtual-key code for the "S" key
						Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedS = TRUE;
					}
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
				{
					INPUT Inputs[1] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "A" key
					Inputs[0].ki.wVk = 65; // virtual-key code for the "A" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					SendInput(1, Inputs, sizeof(INPUT));

					Sleep(MOVEMENTDELAY);

					releasedA = FALSE;
				}
				else
				{
					if (releasedA == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						// Complete a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Release the "A" key
						Inputs[0].ki.wVk = 65; // virtual-key code for the "A" key
						Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedA = TRUE;
					}
				}
				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
				{
					INPUT Inputs[1] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "D" key
					Inputs[0].ki.wVk = 68; // virtual-key code for the "D" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					SendInput(1, Inputs, sizeof(INPUT));

					Sleep(MOVEMENTDELAY);

					releasedD = FALSE;
				}
				else
				{
					if (releasedD == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						// Complete a generic keyboard event.
						Inputs[0].type = INPUT_KEYBOARD;
						Inputs[0].ki.wScan = 0; // hardware scan code for key
						Inputs[0].ki.time = 0;
						Inputs[0].ki.dwExtraInfo = 0;

						// Release the "D" key
						Inputs[0].ki.wVk = 68; // virtual-key code for the "D" key
						Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press

						SendInput(1, Inputs, sizeof(INPUT));

						releasedD = TRUE;
					}
				}

				if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
				{
					INPUT Inputs[1] = { 0 };

					Inputs[0].type = INPUT_MOUSE;
					Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

					SendInput(1, Inputs, sizeof(INPUT));

					Sleep(BUTTONDELAY);

					releasedLClick = FALSE;
				}
				else
				{
					if (releasedLClick == FALSE)
					{
						INPUT Inputs[1] = { 0 };

						Inputs[0].type = INPUT_MOUSE;
						Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;

						SendInput(1, Inputs, sizeof(INPUT));

						releasedLClick = TRUE;
					}
				}
			}
			else
			{			
				XinputLoaded = FALSE;
				if (!XinputNotice)
				{
					cout << "Error: Unable to locate XBOX One controller..." << endl;

					XinputNotice = TRUE;

					INPUT Inputs[2] = { 0 };

					// Set up a generic keyboard event.
					Inputs[0].type = INPUT_KEYBOARD;
					Inputs[0].ki.wScan = 0; // hardware scan code for key
					Inputs[0].ki.time = 0;
					Inputs[0].ki.dwExtraInfo = 0;

					// Press the "Esc" key
					Inputs[0].ki.wVk = 27; // virtual-key code for the "Esc" key
					Inputs[0].ki.dwFlags = 0; // 0 for key press

					// Complete a generic keyboard event.
					Inputs[1].type = INPUT_KEYBOARD;
					Inputs[1].ki.wScan = 0; // hardware scan code for key
					Inputs[1].ki.time = 0;
					Inputs[1].ki.dwExtraInfo = 0;

					// Release the "Esc" key
					Inputs[1].ki.wVk = 27; // virtual-key code for the "Esc" key
					Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 0 for key press
					SendInput(2, Inputs, sizeof(INPUT));
				}
			}
			Sleep(15);
		}

		break;
	}
	
	return TRUE;
}

HANDLE MakeThread(LPVOID Process, LPVOID Parameter)
{
	HANDLE Thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Process, Parameter, NULL, NULL);
	if (!Thread) return NULL;
	return Thread;
}

VOID DestroyThread(HANDLE Thread, DWORD Parameter, DWORD MaxWaitTime)
{
	TerminateThread(Thread, Parameter);
	WaitForSingleObject(Thread, MaxWaitTime);
	CloseHandle(Thread);
}

VOID CreateXinputThreads()
{
	MakeThread((LPVOID)Threads, (LPVOID)XINPUT);
}

VOID DestroyXinputThreads()
{
	if (XinputThread)
	{
		DestroyThread(XinputThread, 0, INFINITE);
	}
}