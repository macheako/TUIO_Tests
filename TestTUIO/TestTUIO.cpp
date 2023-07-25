// TestTUIO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "TuioServer.h"
#include "TuioCursor.h"
#include "TuioTime.h"

#include <iostream>
#include <Windows.h>

int main(int argc, char ** argv)
{
	TUIO::TuioServer* server = NULL;
	if (argc == 3) {
		server = new TUIO::TuioServer(argv[1], atoi(argv[2]));
	}
	else server = new TUIO::TuioServer(); // default is UDP port 3333 on localhost

	server->enableFullUpdate();
	server->disablePeriodicMessages();

	server->initFrame(TUIO::TuioTime::getSessionTime());

	TUIO::TuioCursor* cursor2 = new TUIO::TuioCursor(1, 1, 0, 0);
	//TUIO::TuioCursor* cursor3 = new TUIO::TuioCursor(1, 5, 0, 0);
	//TUIO::TuioCursor* cursor1 = new TUIO::TuioCursor(1, 1, 0, 0);

	TUIO::TuioCursor* cursor = cursor2;

	server->addExternalTuioCursor(cursor);
	cursor->setSessionID(2);
	//server->addExternalTuioCursor(cursor3); 

	server->commitFrame();

	std::cout << "Cursor ID : " << cursor->getCursorID() << " Session ID : " << cursor->getSessionID() << std::endl;	

	system("pause");

	for (int i = 0; i < 10; ++i)
	{
		auto session_time = TUIO::TuioTime::getSessionTime();
		//server->initFrame(session_time);

		auto last_x = cursor->getX();
		auto last_y = cursor->getY();

		// std::cout << "Current Location (" << last_x << ", " << last_y << " )" << std::endl;		

		std::cout << "Session ID " << cursor->getSessionID() << " Time " << TUIO::TuioTime::getSessionTime().getTotalMilliseconds() << " ms" << std::endl;

		cursor->update(session_time, .5, .5);
		server->updateExternalTuioCursor(cursor);
		server->commitFrame();

		Sleep(200);
	}

	cursor->update(TUIO::TuioTime::getSessionTime(), -1, -1);
	server->updateExternalTuioCursor(cursor);
	server->commitFrame();

	system("pause");

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
