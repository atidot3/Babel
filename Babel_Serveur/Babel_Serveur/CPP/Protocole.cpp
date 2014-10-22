#include	"Include\Protocole.h"

Protocole::Protocole()
{
}
Protocole::~Protocole()
{
}
void		Protocole::Welcome(const std::string pseudo)
{
}
void		Protocole::Contact_List(const std::string pseudo)
{
}
void		Protocole::Contact_Add(const std::string pseudo)
{
}
void		Protocole::Contact_Remove(const std::string pseudo)
{
}
void		Protocole::Contact_Call_Me(const std::string pseudo)
{
}
void		Protocole::Contact_To_Call(const std::string pseudo)
{
}
void		Protocole::Protocole_to_call(const int id, const std::string Str)
{
	switch (id)
	{
		case WELCOME:
		{
			this->Contact_Call_Me(Str);
			break;
		}
		case CONTACT_LIST:
		{
			this->Contact_Call_Me(Str);
			break;
		}
		case CONTACT_ADD:
		{
			this->Contact_Call_Me(Str);
			break;
		}
		case CONTACT_REMOVE:
		{
			this->Contact_Call_Me(Str);
			break;
		}
		case CONTACT_CALL_ME:
		{
			this->Contact_Call_Me(Str);
			break;
		}
		case CONTACT_TO_CALL:
		{
			this->Contact_To_Call(Str);
			break;
		}
		default:
		{
			Logger::Instance()->log(2, "Protocole: Unknow enum\n");
			break;
		}
	}
}