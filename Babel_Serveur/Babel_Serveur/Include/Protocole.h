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
  typedef				void (Protocole::*ptr)(const std::string &);

 private:
  enum			PROTOCOLE_ENUM
  {
    PROTOCOLE_BEGIN = 0,
    SALUT,
    AUTH,
    CONTACT_LIST,
    CONTACT_ADD,
    CONTACT_REMOVE,
    CONTACT_CALL_ME,
    CONTACT_TO_CALL,
    PROTOCOLE_END
  };
  ptr			func_tab[7];
 public:
  Protocole();
  ~Protocole();
  void			Protocole_to_call(const int id, const std::string &str);
 private:
  void			Welcome(const std::string &pseudo);
  void			Contact_List(const std::string &pseudo);
  void			Contact_Add(const std::string &pseudo);
  void			Contact_Remove(const std::string &pseudo);
  void			Contact_Call_Me(const std::string &pseudo);
  void			Contact_To_Call(const std::string &pseudo);
  void			Authentification(const std::string &pseudo);
};

#endif // PROTOCOLE
