#include		<iostream>
#include		"Select.hh"

Select::Select(Server *server)
{
  cs = server->getSock()->realSock();
  server->getSock()->bind();
  server->getSock()->listen();
}

Select::~Select()
{
}

bool			Select::init(Server *server)
{
  int			i;
  Client*		client;

  i = 0;
  FD_ZERO(&readfds);
  FD_ZERO(&writefds);
  FD_SET(server->getSock()->realSock(), &readfds);
  while ((client = server->getClient(i, NULL)))
    {

      if (server->getClient(i)->getSock()->realSock() > cs)
	cs = server->getClient(i)->getSock()->realSock();
      FD_SET(server->getClient(i)->getSock()->realSock(), &readfds);
      if (server->getClient(i)->getSending() != NULL)
	FD_SET(server->getClient(i)->getSock()->realSock(), &writefds);
      ++i;
    }
  return (true);
}

int			Select::waitFds(Server *server)
{
  ISocket		*client_sock;
  int			ret;

  client_sock = NULL;
  this->init(server);
  ret = select(this->cs + 1, &readfds, &writefds, NULL, NULL);
  return (ret);
}

void			Select::sendThings(Server *server)
{
  int			i;
  Client*		client;

  i = 0;
  while ((client = server->getClient(i)))
    {
      if (FD_ISSET(client->getSock()->realSock(), &writefds))
	{
	  client->getSock()->sendToSomeone(client->getSending(), client->getIp(), PORT);
	  client->setSending(NULL);
	}
      ++i;
    }
}

void			Select::recvThings(Server *server)
{
  int			i;
  Client*		client;
  Proto_Struct		*proto = new Proto_Struct;

  i = 0;
  while ((client = server->getClient(i)))
    {
      if (FD_ISSET(client->getSock()->realSock(), &readfds))
	{
	  client->getSock()->recvFromSomeone(client->getIp(), PORT, proto);
	  client->setReceiving(proto);
	}
      ++i;
    }
}

bool			Select::isThereNewClient(Server *server)
{
  if (FD_ISSET(server->getSock()->realSock(), &readfds))
    return (true);
  return (false);
}
