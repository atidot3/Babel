#include	<iostream>
#include	"Include\Protocole.hh"
#include	"Include\Server.hh"

Server::Server()
{
  _sock = new AbstractSocket();
  _maxId= 0;
}

Server::~Server()
{
  _sock->close();
}

ISocket*	Server::getSock() const
{
  return (this->_sock);
}

std::list<Client*>	Server::getListClient() const
{
  return (clients);
}

Client*			Server::getClient(int id)
{
  std::list<Client*>::iterator	it;

  it = clients.begin();
  while (it != clients.end() && id != (*it)->getId())
    ++it;
  if (it == clients.end())
    return (NULL);
  return (*it);
}

Client*			Server::getClient(const std::string &pseudo)
{
  std::list<Client*>::iterator	it;

  it = clients.begin();
  while (it != clients.end() && pseudo != (*it)->getPseudo())
    ++it;
  if (it == clients.end())
    return (NULL);
  return (*it);
}

Client*			Server::getClient(int nb, void* null)
{
  std::list<Client*>::iterator	it;
  int			i;

  i = 0;
  it = clients.begin();
  while (it != clients.end() && i < nb)
    {
      ++it;
      ++i;
    }
  if (it == clients.end())
    return (NULL);
  return (*it);
}

void			Server::addClient()
{
  Client		*client = new Client(_maxId);
  ISocket		*sock;
  Protocole		proto;

  sock = _sock->accept();
  client->setSock(sock);
  clients.push_back(client);
  ++_maxId;
  proto.Welcome(this, client);
}

void			Server::removeClient(int clientId)
{
  std::list<Client *>::iterator	it;
  Client*		tmp;

  it = clients.begin();
  while (it != clients.end() && clientId != (*it)->getId())
    ++it;
  if (it != clients.end())
    {
      tmp = *it;
      clients.erase(it);
      tmp->getSock()->close();
    }
}

void			Server::gestClient()
{
  Protocole		protocole;
  std::list<Client *>::iterator it;

  it = clients.begin();
  while (it != clients.end())
    {
      if (protocole.Protocole_to_call(this, *it) == false)
		it = clients.begin();
      else
		++it;
    }
}
