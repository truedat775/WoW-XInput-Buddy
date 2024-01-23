// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static bool InitMsg = false;

int _tmain(int argc, _TCHAR* argv[])
{
	//Below our variables are defined. number A, number B, and numberC is the result
	char Result1[128] = "Enabling Xinput! XBOX controller will run in the background until windows shuts down.";
	char Result2[128] = "Exiting Xinput Buddy...  Goodbye!";

	// the operation to be performed 
	char op;

	if (InitMsg == false)
	{
		cout << "WoW Xinput Buddy 1.00 for World of Warcraft" << endl;
		cout << "Copyright (c) 2023 Sierra Industries" << endl;
		cout << "Paypal Donate: addiserve@hotmail.com" << endl;

		cout << " " << endl;

		cout << "Welcome to the WoW Xinput Buddy!" << endl;
		cout << "This program must be run as administrator." << endl;

		cout << " " << endl;

		cout << "You'll be asked to enter a number followed signifying the operation you'd" << endl << "like to perform." << endl;

		cout << " " << endl;

		InitMsg = true;
	}

	cout << "Options: " << endl;
	cout << "1 - Start" << endl;
	cout << "2 - Close" << endl;
	cout << "3 - Help" << endl;

	cout << " " << endl;

	cout << "Enter a number to begin the operation: ";
	cin >> op; // set variable
	cout << " " << endl;
	switch (op) {
	case '1':
		cout << Result1 << endl;

		Sleep(5000);

		break;
	case '2':
		cout << Result2 << endl;

		//DestroyXinputThreads();

		cout << " " << endl;

		system("pause");

		return 0;
	case '3':
		cout << "[XBOX One Controller Layout]" << endl;
		cout << " " << endl;
		cout << "A - Select Cursor, Accept (Left Click)" << endl;
		cout << "X - Right Click, Use Item, Loot, Etc (Right Click)" << endl;
		cout << "Y - Skill (9)" << endl;
		cout << "B - Skill (0)" << endl;
		cout << "X + Left Shoulder - Loot All (Right Click + Shift)" << endl;
		cout << "Y + Left Shoulder - Sheath/Unsheath Weapon (Z)" << endl;
		cout << "Right Shoulder - Move Cursor" << endl;
		cout << "Left Shoulder - Slow Cursor" << endl;
		cout << "Start - Skill (=)" << endl;
		cout << "Back - Skill (-)" << endl;
		cout << "Directional Pad - Move Character" << endl;
		cout << "Directional Pad + X - Jump (Space)" << endl;
		cout << "Directional Pad + Right Shoulder + A - Move Camera" << endl;
		cout << "Right Shoulder + Start - Map (M)" << endl;
		cout << "Right Shoulder + Right Joystick Up - Camera Zoom In (F3*)" << endl;
		cout << "Right Shoulder + Right Joystick Down - Camera Zoom Out (F4*)" << endl;
		cout << "Right Shoulder + Right Joystick Left - Show Enemies/Enemy Healthbars (V)" << endl;
		cout << "Right Shoulder + Right Joystick Right - Run/Walk (Numpad /)" << endl;
		cout << "Right Shoulder + B - Close Menu (Esc)" << endl;
		cout << "Right Shoulder + Y - Inventory/Bags (Shift + B)" << endl;
		cout << "Right Shoulder + Back - Quest Log (L)" << endl;
		cout << "Right Shoulder + Left Joystick Up - Character/Stats (C)" << endl;
		cout << "Right Shoulder + Left Joystick Down - Talents (N)" << endl;
		cout << "Right Shoulder + Left Joystick Right - Spellbook (P)" << endl;
		cout << "Right Shoulder + Left Joystick Left - Achievements (Y)" << endl;
		cout << "Left Joystick - Skill (1-4)" << endl;
		cout << "Right Joystick - Skill (5-8)" << endl;
		cout << "Left Shoulder + Left Joystick - Skillbar (1-4 + Shift)" << endl;
		cout << "Left Shoulder + Right Joystick - Skillbar (5-6 + Shift)" << endl;
		cout << "Right Shoulder + Left Shoulder + Y - Swim Up/Jump (Space)" << endl;
		cout << "Right Shoulder + Left Shoulder + B - Swim Down/Sit (X)" << endl;
		cout << " " << endl;
		cout << "* These key assignments must be set manually from the games's configuration." << endl;
		cout << " " << endl;
		cout << "Note: Untested on Battle.net, third party programs may result in account closure." << endl;

		cout << " " << endl;

		system("pause");

		return 0;
	default:
		// error message for unknown operator
		cout << "Error: unknown operator - stick to the rules, fella!" << endl;

		cout << " " << endl;

		system("pause");
	}

	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);

	CreateXinputThreads();

	system("pause");

	return 0;
}

