#include	<iostream>
#include	"Include\Client.hh"

Client::Client(int id)
{
  _sock = NULL;
  _ip = "";
  _pseudo = "";
  _contacts = NULL;
  _id = id;
  _sending = NULL;
  _receiving = NULL;
}

Client::Client(ISocket *sock, int id)
{
  _sock = sock;
  _ip = "";
  _pseudo = "";
  _id = id;
  _sending = NULL;
  _receiving = NULL;
}

Client::Client(ISocket *sock, const std::string &ip, int id)
{
  _sock = sock;
  _ip = ip;
  _id = id;
  _sending = NULL;
  _receiving = NULL;
}

Client::Client(ISocket *sock, const std::string &ip, const std::string &pseudo, int id)
{
  _sock = sock;
  _ip = ip;
  _pseudo = pseudo;
  _id = id;
  _sending = NULL;
  _receiving = NULL;
}

Client::~Client()
{
  _sock->close();
}

ISocket*		Client::getSock() const
{
  return (_sock);
}

std::string		Client::getIp() const
{
  return (_ip);
}

std::string		Client::getPseudo() const
{
  return (_pseudo);
}

FileContact*		Client::getContacts() const
{
  return (_contacts);
}

Proto_Struct*		Client::getSending() const
{
  return (_sending);
}

Proto_Struct*	Client::getReceiving() const
{
  return (_receiving);
}

int			Client::getId() const
{
  return (_id);
}
void			Client::setSock(ISocket *sock)
{
  _sock = sock;
}

void			Client::setIp(const std::string &ip)
{
  _ip = ip;
  std::cout << _pseudo << std::endl;
  _contacts = new FileContact(_pseudo);
}

void			Client::setPseudo(const std::string &pseudo)
{
  _pseudo = pseudo;
}

void			Client::setSending(Proto_Struct *sending)
{
  // if (_sending)
  //   delete (_sending);
  _sending = sending;
}

void			Client::setReceiving(Proto_Struct *receiving)
{
  // if (_receiving)
  //   delete (_receiving);
  _receiving = receiving;
}

void			Client::setId(int id)
{
  _id = id;
}
