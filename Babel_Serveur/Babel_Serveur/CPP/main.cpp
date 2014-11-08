#include <string>
#include <cstring>
#include <iostream>
#include <exception>
#include "Include/Server.hh"
#include "Include/Select.hh"
#include "Include/Client.hh"
#include "Include/ISocket.hh"

int	main()
{
	try
	{
		Server server;
		Select select(&server);

		while (select.waitFds(&server) != -1)
		{
			if (select.isThereNewClient(&server) == true)
				server.addClient();
			select.sendThings(&server);
			select.recvThings(&server);
			server.gestClient();
		}
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
  return (0);
}
