// Babel_Serveur.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include "Include\server.h"
#include <stdlib.h>
#include <vector>
#include "Include\log.h"

using namespace std;

int	main()
{
	Logger::Instance()->open("Server.txt");
	Logger::Instance()->log(0, "----------------Server Initialized-------------\n");
	srand(43);
	try 
	{
		Server	serv;
		serv.run();
    } 
	catch (std::exception* e)
	{
        std::cerr << e->what() << std::endl;
		Logger::Instance()->log(3, e->what());
        delete e;
    }
	Logger::Instance()->log(0, "Exit with code 0");
    return 0;
}