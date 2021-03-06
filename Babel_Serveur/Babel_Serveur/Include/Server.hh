#ifndef		SERVER_HH_
# define	SERVER_HH_

# include	<list>

# include	"Include/ISocket.hh"
# include	"Include/Client.hh"

class		Server
{
private:
  int		_maxId;
  ISocket*	_sock;
  std::list<Client *> clients;

public:
  Server();
  ~Server();
  ISocket*		getSock() const;
  std::list<Client *>	getListClient() const;
  Client*		getClient(int);
  Client*		getClient(int, void *);
  Client*		getClient(const std::string &);
  void			addClient();
  void			removeClient(int);
  void			gestClient();
};

#endif
