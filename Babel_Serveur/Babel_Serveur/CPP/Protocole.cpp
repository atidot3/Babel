#include	<cstring>
#include	"Include/Protocole.h"
#include	"Include/server.h"

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

void		Protocole::Welcome(Struct_Proto *t, Server* srv)
{
	std::cout << "Welcome" << std::endl;
	if (strcmp(t->Buffer, "salut") == 0)
	{
		Struct_Proto r;
		r.audio = 0;
		r.EnumId = SALUT;
		strcpy(r.ip, t->ip);
		strcpy(r.Buffer, "salut");
		srv->socket->sendToSomeone(&r, r.ip, CLIENT_PORT);
	}
}

void		Protocole::Contact_List(Struct_Proto *t, Server* srv)
{
	std::cout << "Contact_List" << std::endl;
}

void		Protocole::Contact_Add(Struct_Proto *t, Server* srv)
{
	std::cout << "Contact_Add" << std::endl;
	if ((srv->FindUser(t->myPseudo)) == true)
	{
		Client* tmp = srv->GetUserSession(t->myPseudo);
		if (tmp)
		{
			if (t->Buffer != NULL)
				if ((tmp->addContact(t->Buffer)) == true)
				{
					Struct_Proto r;
					r.audio = 0;
					r.EnumId = CONTACT_ADD;
					strcpy(r.ip, t->ip);
					strcpy(r.Buffer, "ok");
					srv->socket->sendToSomeone(&r, r.ip, CLIENT_PORT);
				}
				else
				{
					Logger::Instance()->log(2, "Protocole: Contact_Add error adding contact\n");
					Struct_Proto r;
					r.audio = 0;
					r.EnumId = CONTACT_ADD;
					strcpy(r.ip, t->ip);
					strcpy(r.Buffer, "bad");
					srv->socket->sendToSomeone(&r, r.ip, CLIENT_PORT);
				}
		}
	}
}

void		Protocole::Contact_Remove(Struct_Proto *t, Server* srv)
{
	std::cout << "Contact_Remove" << std::endl;
	if ((srv->FindUser(t->myPseudo)) == true)
	{
		Client* tmp = srv->GetUserSession(t->myPseudo);
		if (tmp)
		{
			if (t->Buffer != NULL)
				if ((tmp->removeContact(t->Buffer)) == true)
				{
					Struct_Proto r;
					r.audio = 0;
					r.EnumId = CONTACT_REMOVE;
					strcpy(r.ip, t->ip);
					strcpy(r.Buffer, "ok");
					srv->socket->sendToSomeone(&r, r.ip, CLIENT_PORT);
				}
				else
				{
					Logger::Instance()->log(2, "Protocole: Contact_Remove error removing contact\n");
					Struct_Proto r;
					r.audio = 0;
					r.EnumId = CONTACT_REMOVE;
					strcpy(r.ip, t->ip);
					strcpy(r.Buffer, "bad");
					srv->socket->sendToSomeone(&r, r.ip, CLIENT_PORT);
				}
		}
	}
}

void		Protocole::Contact_Call_Me(Struct_Proto *t, Server* srv)
{
	std::cout << "Contact_Call_Me" << std::endl;
}

void		Protocole::Contact_To_Call(Struct_Proto *t, Server* srv)
{
	std::cout << "Contact_To_Call" << std::endl;
}

void		Protocole::Authentification(Struct_Proto *t, Server* srv)
{
	std::cout << "Auth" << std::endl;
	if (t->Buffer != NULL)
	{
		Client* newOne = new Client(t->Buffer);
		if ((srv->AddUser(t->Buffer, newOne)) == true)
		{
			Struct_Proto r;
			r.audio = 0;
			r.EnumId = AUTH;
			strcpy(r.ip, t->ip);
			strcpy(r.Buffer, "ok");
			srv->socket->sendToSomeone(&r, r.ip, CLIENT_PORT);
		}
		else
		{
			Logger::Instance()->log(2, "Protocole: Authentification error adding new client\n");
			Struct_Proto r;
			r.audio = 0;
			r.EnumId = AUTH;
			strcpy(r.ip, t->ip);
			strcpy(r.Buffer, "bad");
			srv->socket->sendToSomeone(&r, r.ip, CLIENT_PORT);
		}
	}
}
void		Protocole::Send_Audio(Struct_Proto *t, Server* srv)
{
	std::cout << "send audio" << std::endl;
}
void		Protocole::Disconnect(Struct_Proto *t, Server* srv)
{
	std::cout << "Client " << t->myPseudo << " had requested disconnection" << std::endl;
	if ((srv->RemoveUser(t->Buffer)) == true)
	{
		Logger::Instance()->log(2, "Protocole: Disconnect error removing client\n");
	}
	else
	{
		std::cout << "Client " << (string)t->myPseudo << " disconnected" << std::endl;
	}
}
void		Protocole::Protocole_to_call(Struct_Proto *t, Server* srv)
{
	int id = t->EnumId;
  if (id - 1 > 9)
    Logger::Instance()->log(2, "Protocole: Unknow enum\n");
  else
	(*this.*func_tab[id - 1])(t, srv);
}
