#include <string>
#include <cstring>
#include <iostream>
#include <exception>
#include <signal.h>
#include "Include/Server.hh"
#include "Include/Select.hh"
#include "Include/Client.hh"
#include "Include/ISocket.hh"
#include "Include/BabelException.hpp"

Server *g_server;

void	signalHandler(int signum)
{
  int	i;
  Client *client;

  i = 0;
  while ((client = g_server->getClient(i, NULL)))
    g_server->removeClient(client->getId());
}

int	main()
{
  try
    {
      Server server;
      Select select(&server);

      g_server = &server; 
      signal(SIGINT, signalHandler);
      while (select.waitFds(&server) != -1)
	{
	  if (select.isThereNewClient(&server) == true)
	    server.addClient();
	  select.sendThings(&server);
	  select.recvThings(&server);
	  server.gestClient();
	}
    }
  catch (const BabelException &e)
    {
      std::cout << e.what() << std::endl;
    }
  return (0);
}
