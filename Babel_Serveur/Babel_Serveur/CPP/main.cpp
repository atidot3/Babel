#include <string>
#include <cstring>
#include <iostream>
#include "Include\Server.hh"
#include "Include\Select.hh"
#include "Include\Client.hh"
#include "Include\ISocket.hh"

int	main()
{
	Server server;
	Select select(&server);

	while (select.waitFds(&server) != -1)
	{
		//std::cout << "wtf" << std::endl;
		if (select.isThereNewClient(&server) == true)
			server.addClient();
		//std::cout << "wesh" << std::endl;
		select.sendThings(&server);
		//std::cout << "yolo" << std::endl;
		select.recvThings(&server);
		//std::cout << "gneh" << std::endl;
		server.gestClient();
		//std::cout << "yata" << std::endl;
	}
  return (0);
}
