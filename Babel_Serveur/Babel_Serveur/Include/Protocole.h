#ifndef			PROTOCOLE
# define		PROTOCOLE

#include			<list>
#include			<iostream>
#include			<map>
#include			"Include\log.h"

struct				Proto_Struct
{
	int				EnumId;
	char			Buffer[512];
	int				audio;
};
typedef				Proto_Struct Struct_Proto;
class				Protocole
{
private:
	enum			PROTOCOLE_ENUM
	{
		PROTOCOLE_BEGIN = 0,
	    SALUT,
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
	void			Welcome(std::string pseudo);
	void			Contact_List(std::string pseudo);
	void			Contact_Add(std::string pseudo);
	void			Contact_Remove(std::string pseudo);
	void			Contact_Call_Me(std::string pseudo);
	void			Contact_To_Call(std::string pseudo);
};

#endif // PROTOCOLE