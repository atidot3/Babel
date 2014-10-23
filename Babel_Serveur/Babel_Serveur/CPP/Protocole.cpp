#include	"Include/Protocole.h"
#include	"Include\server.h"

Protocole::Protocole()
{
  func_tab[0] = &Protocole::Welcome;
  func_tab[1] = &Protocole::Contact_List;
  func_tab[2] = &Protocole::Contact_Add;
  func_tab[3] = &Protocole::Contact_Remove;
  func_tab[4] = &Protocole::Contact_Call_Me;
  func_tab[5] = &Protocole::Contact_To_Call;
  func_tab[6] = &Protocole::Authentification;
}

Protocole::~Protocole()
{
}

void		Protocole::Welcome(Struct_Proto *t, const Server* srv)
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

void		Protocole::Contact_List(Struct_Proto *t, const Server* srv)
{
	std::cout << "Contact_List" << std::endl;
}

void		Protocole::Contact_Add(Struct_Proto *t, const Server* srv)
{
	std::cout << "Contact_Add" << std::endl;
}

void		Protocole::Contact_Remove(Struct_Proto *t, const Server* srv)
{
	std::cout << "Contact_Remove" << std::endl;
}

void		Protocole::Contact_Call_Me(Struct_Proto *t, const Server* srv)
{
	std::cout << "Contact_Call_Me" << std::endl;
}

void		Protocole::Contact_To_Call(Struct_Proto *t, const Server* srv)
{
	std::cout << "Contact_To_Call" << std::endl;
}

void		Protocole::Authentification(Struct_Proto *t, const Server* srv)
{
	std::cout << "Auth" << std::endl;
}

void		Protocole::Protocole_to_call(Struct_Proto *t, Server* srv)
{
	int id = t->EnumId;
  if (id - 1 > 6)
    Logger::Instance()->log(2, "Protocole: Unknow enum\n");
  else
	(*this.*func_tab[id - 1])(t, srv);
}
