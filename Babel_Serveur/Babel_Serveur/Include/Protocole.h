#ifndef			PROTOCOLE
# define		PROTOCOLE

#include			<list>
#include			<iostream>
#include			<map>
#include			"Include\log.h"

class				Server;

struct				Proto_Struct
{
	int				EnumId;
	char			Buffer[512];
	int				audio;
	char			ip[100];
};

typedef				Proto_Struct Struct_Proto;

class				Protocole
{
  typedef				void (Protocole::*ptr)(Struct_Proto *t, const Server*);

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
  void			Protocole_to_call(Struct_Proto *t, Server* srv);
 private:
  void			Welcome(Struct_Proto *t, const Server*);
  void			Contact_List(Struct_Proto *t, const Server*);
  void			Contact_Add(Struct_Proto *t, const Server*);
  void			Contact_Remove(Struct_Proto *t, const Server*);
  void			Contact_Call_Me(Struct_Proto *t, const Server*);
  void			Contact_To_Call(Struct_Proto *t, const Server*);
  void			Authentification(Struct_Proto *t, const Server*);
};

#endif // PROTOCOLE
