#include			"Server.h"

Server::Server()
{
  sock = new Socket(PORT_SERVER, 42, "TCP");
  running = true;
}

Server::~Server()
{
  delete (sock);
}

void				Server::start()
{
  while (running = true)
    {
      
    }
}

void				Server::stop()
{
  running = false;
}
