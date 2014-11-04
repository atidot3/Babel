#include	<iostream>
#include	<cstring>
#include	"Protocole.hh"
#include	"Server.hh"

Protocole::Protocole()
{
  func_tab[0] = &Protocole::Welcome;
  func_tab[1] = &Protocole::Authentification;
  func_tab[2] = &Protocole::Contact_List;
  func_tab[3] = &Protocole::Contact_Add;
  func_tab[4] = &Protocole::Contact_Remove;
  func_tab[5] = &Protocole::Contact_Call_Me;
  func_tab[6] = &Protocole::Contact_To_Call;
  func_tab[7] = &Protocole::Send_Audio;
  func_tab[8] = &Protocole::Disconnect;
}

Protocole::~Protocole()
{
}

void		Protocole::Welcome(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;

  proto->cmd = WELCOME;
  memset(proto->buffer, 0, 512);
  strcpy(proto->buffer, "WELCOME");
  client->setSending(proto);
}

void		Protocole::Contact_List(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;
  std::string	contact_list = "";
  std::list<std::string>*	list;
  std::list<std::string>::iterator it;
  bool				check = false;

  std::cout << "Contact_List" << std::endl;
  proto->cmd = CONTACT_LIST;
  memset(proto->buffer, 0, 512);
  list = client->getContacts()->getList();
  it = list->begin();
  while (it != list->end())
    {
      check = true;
      contact_list += *it;
      ++it;
      if (it != list->end())
	contact_list += " ";
    }
  if (check == true)
    strcpy(proto->buffer, contact_list.c_str());
  client->setSending(proto);  
}

void		Protocole::Contact_Add(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;

  proto->cmd = CONTACT_ADD;
  memset(proto->buffer, 0, 512);
  std::cout << "Contact_Add" << std::endl;
  if (client->getContacts()->add(client->getReceiving()->buffer) == false)
    strcpy(proto->buffer, "ko");
  else
  strcpy(proto->buffer, "ok");
  client->setSending(proto);
}

void		Protocole::Contact_Remove(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;

  proto->cmd = CONTACT_REMOVE;
  memset(proto->buffer, 0, 512);
  std::cout << "Contact_Remove" << std::endl;
  if (client->getContacts()->erase(client->getReceiving()->buffer) == false)
    strcpy(proto->buffer, "ko");
  else
    strcpy(proto->buffer, "ok");
  client->setSending(proto);
}

void		Protocole::Contact_Call_Me(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;
  Client	*other;

  proto->cmd = CONTACT_CALL_ME;
  memset(proto->buffer, 0, 512);
  std::cout << "Contact_Call_Me" << std::endl;
  if ((other = server->getClient(client->getReceiving()->buffer)) == NULL)
    {
      strcpy(proto->buffer, client->getIp().c_str());
      other->setSending(proto);
      memset(proto->buffer, 0, 512);
      strcpy(proto->buffer, "ok");
    }
  else
    strcpy(proto->buffer, "ko");
  client->setSending(proto);  
}

void		Protocole::Contact_To_Call(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;
  Client	*other;

  proto->cmd = CONTACT_TO_CALL;
  memset(proto->buffer, 0, 512);
  std::cout << "Contact_To_Call" << std::endl;
  if ((other = server->getClient(client->getReceiving()->buffer)) == NULL)
    {
      strcpy(proto->buffer, client->getPseudo().c_str());
      other->setSending(proto);
      memset(proto->buffer, 0, 512);
      strcpy(proto->buffer, "ok");
    }
  else
    strcpy(proto->buffer, "ko");
  client->setSending(proto);
}

void		Protocole::Authentification(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;

  memset(proto->buffer, 0, 512);
  std::cout << "Auth" << std::endl;
  if (client->getPseudo() == "")
    client->setPseudo(client->getReceiving()->buffer);
  else
    client->setIp(client->getReceiving()->buffer);
  proto->cmd = AUTH;
  strcpy(proto->buffer, "ok");
  client->setSending(proto);
}
void		Protocole::Send_Audio(Server *server, Client *client)
{
	std::cout << "send audio" << std::endl;
}
void		Protocole::Disconnect(Server *server, Client *client)
{
  server->removeClient(client->getId());
  std::cout << "Client " << client->getPseudo() << " had requested disconnection" << std::endl;
}

bool		Protocole::Protocole_to_call(Server *server, Client *client)
{
  int id;

  id = 0;
  if (client->getReceiving())
    {
      id = client->getReceiving()->cmd;
      if (id > 8)
	std::cout << "Protcole: Unknow enum" << std::endl;
      //    Logger::Instance()->log(2, "Protocole: Unknow enum\n");
      else
	{
	  (*this.*func_tab[id])(server, client);
	  client->setReceiving(NULL);
	  if (id == 8)
	    return (false);
	}
    }
  return (true);
}
