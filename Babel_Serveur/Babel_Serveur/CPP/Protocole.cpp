#include	<iostream>
#include	<cstring>
#include	"Include/Protocole.hh"
#include	"Include/Server.hh"

Protocole::Protocole()
{
  func_tab[0] = &Protocole::Welcome;
  func_tab[1] = &Protocole::Authentification;
  func_tab[2] = &Protocole::Contact_List;
  func_tab[3] = &Protocole::Contact_Add;
  func_tab[4] = &Protocole::Contact_Remove;
  func_tab[5] = &Protocole::Contact_Call_Me;
  func_tab[6] = &Protocole::Contact_Call_Refuse;
  func_tab[7] = &Protocole::Contact_To_Call;
  func_tab[8] = &Protocole::Disconnect;
}

Protocole::~Protocole()
{
}

bool		Protocole::Welcome(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;

  proto->cmd = WELCOME;
  memset(proto->buffer, 0, 512);
  strcpy(proto->buffer, "WELCOME");
  client->setSending(proto);
  return (true);
}

bool		Protocole::Contact_List(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;
  std::string	contact_list = "";
  std::list<std::string>*	list;
  std::list<std::string>::iterator it;
  bool				check = false;

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
  return (true);
}

bool		Protocole::Contact_Add(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;

  proto->cmd = CONTACT_ADD;
  memset(proto->buffer, 0, 512);
  if (client->getContacts()->add(client->getReceiving()->buffer) == false)
    strcpy(proto->buffer, "ko");
  else
  strcpy(proto->buffer, "ok");
  client->setSending(proto);
  return (true);
}

bool		Protocole::Contact_Remove(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;

  proto->cmd = CONTACT_REMOVE;
  memset(proto->buffer, 0, 512);
  if (client->getContacts()->erase(client->getReceiving()->buffer) == false)
    strcpy(proto->buffer, "ko");
  else
    strcpy(proto->buffer, "ok");
  client->setSending(proto);
  return (true);
}

bool		Protocole::Contact_Call_Refuse(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;
  Client	*other;

  client->setBusy(false);
  proto->cmd = CONTACT_CALL_REFUSE;
  memset(proto->buffer, 0, 512);
  if ((other = server->getClient(client->getReceiving()->buffer)) != NULL)
    {
      other->setBusy(false);
      other->setSending(proto);
      memset(proto->buffer, 0, 512);
      strcpy(proto->buffer, "ok");
    }
  else
    strcpy(proto->buffer, "ko");
  client->setSending(proto);  
  return (true);
}

bool		Protocole::Contact_Call_Me(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;
  Client	*other;

  proto->cmd = CONTACT_CALL_ME;
  memset(proto->buffer, 0, 512);
  if ((other = server->getClient(client->getReceiving()->buffer)) != NULL)
    {
      strcpy(proto->buffer, client->getIp().c_str());
      other->setSending(proto);
      memset(proto->buffer, 0, 512);
      strcpy(proto->buffer, "ok");
    }
  else
    strcpy(proto->buffer, "ko");
  client->setSending(proto);  
  return (true);
}

bool		Protocole::Contact_To_Call(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;
  Client	*other;

  proto->cmd = CONTACT_TO_CALL;
  memset(proto->buffer, 0, 512);
  if ((other = server->getClient(client->getReceiving()->buffer)) != NULL && other->isBusy() == false)
    {
      other->setBusy(true);
      client->setBusy(true);
      strcpy(proto->buffer, client->getPseudo().c_str());
      other->setSending(proto);
      memset(proto->buffer, 0, 512);
      strcpy(proto->buffer, "ok");
    }
  else
    strcpy(proto->buffer, "ko");
  client->setSending(proto);
  return (true);
}

bool		Protocole::Authentification(Server *server, Client *client)
{
  Proto_Struct	*proto = new Proto_Struct;

  memset(proto->buffer, 0, 512);
  if (client->getPseudo() == "")
    {
      if (server->getClient(client->getReceiving()->buffer) != NULL)
	{
	  strcpy(proto->buffer, "ko");
	  return (false);
	}
      else
	{
	  client->setPseudo(client->getReceiving()->buffer);
	  strcpy(proto->buffer, "ok");
	}
    }
  else
    {
      client->setIp(client->getReceiving()->buffer);
      strcpy(proto->buffer, "ok");    
    }
  proto->cmd = AUTH;
  client->setSending(proto);
  return (true);
}

bool		Protocole::Disconnect(Server *server, Client *client)
{
  std::cout << "Client " << client->getPseudo() << " had requested disconnection" << std::endl;
  return (false);
}

bool		Protocole::Protocole_to_call(Server *server, Client *client)
{
  int id;
  Proto_Struct	*proto = new Proto_Struct;

  id = 0;
  if (client->getReceiving())
    {
      id = client->getReceiving()->cmd;
      if (id > 8)
	{
	  std::cout << "Protcole: Unknow enum" << std::endl;
	  memset(proto->buffer, 0, 512);
	  proto->cmd = client->getReceiving()->cmd;
	  strcpy(proto->buffer, "ko");
	  client->setSending(proto);
	}
      else
	{
	  delete (proto);
	  if ((*this.*func_tab[id])(server, client) == false)
	    {
	      server->removeClient(client->getId());
	      return (false);
	    }
	  else
	    client->setReceiving(NULL);
	}
    }
  return (true);
}
