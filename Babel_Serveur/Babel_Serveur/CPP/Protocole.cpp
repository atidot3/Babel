#include	"Include/Protocole.h"

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

void		Protocole::Welcome(const std::string &pseudo)
{
	std::cout << "Welcome" << std::endl;
}

void		Protocole::Contact_List(const std::string &pseudo)
{
	std::cout << "Contact_List" << std::endl;
}

void		Protocole::Contact_Add(const std::string &pseudo)
{
	std::cout << "Contact_Add" << std::endl;
}

void		Protocole::Contact_Remove(const std::string &pseudo)
{
	std::cout << "Contact_Remove" << std::endl;
}

void		Protocole::Contact_Call_Me(const std::string &pseudo)
{
	std::cout << "Contact_Call_Me" << std::endl;
}

void		Protocole::Contact_To_Call(const std::string &pseudo)
{
	std::cout << "Contact_To_Call" << std::endl;
}

void		Protocole::Authentification(const std::string &pseudo)
{
	std::cout << "Auth" << std::endl;
}

void		Protocole::Protocole_to_call(const int id, const std::string &str)
{
  std::cout << id << std::endl;
  if (id - 1 > 6)
    Logger::Instance()->log(2, "Protocole: Unknow enum\n");
  else
    func_tab[id - 1](str);    
}
