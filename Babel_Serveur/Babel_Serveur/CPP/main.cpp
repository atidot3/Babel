#include <string>
#include <cstring>
#include <iostream>
#include "Server.hh"
#include "Select.hh"
#include "Client.hh"
#include "ISocket.hh"

int	main()
{
  Server server;
  Select select(&server);
  
  while (select.waitFds(&server) != -1)
    {
      //      std::cout << "wtf" << std::endl;
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
