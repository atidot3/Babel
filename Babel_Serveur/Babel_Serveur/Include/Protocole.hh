#ifndef				PROTOCOLE_HH_
# define			PROTOCOLE_HH_

# include			"Include/Server.hh"


class				Protocole
{
  typedef			bool (Protocole::*ptr)(Server *, Client *);

private:
  ptr			func_tab[10];

public:
  Protocole();
  ~Protocole();
  bool			Protocole_to_call(Server *, Client * srv);
  bool			Welcome(Server *, Client *);

private:
  bool			Contact_List(Server *, Client *);
  bool			Contact_Add(Server *, Client *);
  bool			Contact_Remove(Server *, Client *);
  bool			Contact_Call_Me(Server *, Client *);
  bool			Contact_Call_Refuse(Server *, Client *);
  bool			Contact_To_Call(Server *, Client *);
  bool			Authentification(Server *, Client *);
  bool			Disconnect(Server *, Client *);
};

#endif // PROTOCOLE
