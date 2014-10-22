#ifndef			PROTOCOLE
# define		PROTOCOLE

#include			<list>
#include			<iostream>
#include			<map>
#include			"Include\log.h"

class				Protocole
{
private:
	enum			PROTOCOLE_ENUM
	{
		PROTOCOLE_BEGIN = 0,
	    WELCOME,
		CONTACT_LIST,
		CONTACT_ADD,
		CONTACT_REMOVE,
		CONTACT_CALL_ME,
		CONTACT_TO_CALL,
		PROTOCOLE_END
	};
public:
	Protocole();
	~Protocole();
	void			Protocole_to_call(const int id, std::string Str);
private:
	//int pour l'audio
	void			Welcome(std::string pseudo);
	void			Contact_List(std::string pseudo);
	void			Contact_Add(std::string pseudo);
	void			Contact_Remove(std::string pseudo);
	void			Contact_Call_Me(std::string pseudo);
	void			Contact_To_Call(std::string pseudo);
};

#endif