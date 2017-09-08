#include "ServerPCH.h"
#include "..\Engine\SBE.h"
#include <ctime>
#include "ServerMain.h"

void main()
{
	SBI::Input::SBI_Init();
	SBN::Network::Init();

	SBN::Server server(27015);
	server.Bind();
	server.StartListen();

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	int len = 0;


	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
		len = strlen(buffer);
		buffer[len] = 0;

		//std::cout << buffer << std::endl;
		server.SendToAll(buffer, len+1);
		
	}


	SBI::Window* window = SBI::Input::CreateWindowXX(500, 500, "Server");
	while (!window->ShouldClose())
	{
		window->Update();
		window->SwapBuffers();
		glfwPollEvents();
	}
}