#ifndef				PROTOCOLE_HH_
# define			PROTOCOLE_HH_

# include			"Include/Server.hh"


class				Protocole
{
  typedef			void (Protocole::*ptr)(Server *, Client *);

private:
  ptr			func_tab[9];

public:
  Protocole();
  ~Protocole();
  bool			Protocole_to_call(Server *, Client * srv);
  void			Welcome(Server *, Client *);

private:
  void			Contact_List(Server *, Client *);
  void			Contact_Add(Server *, Client *);
  void			Contact_Remove(Server *, Client *);
  void			Contact_Call_Me(Server *, Client *);
  void			Contact_Call_Refuse(Server *, Client *);
  void			Contact_To_Call(Server *, Client *);
  void			Authentification(Server *, Client *);
  void			Send_Audio(Server *, Client *);
  void			Disconnect(Server *, Client *);
};

#endif // PROTOCOLE
