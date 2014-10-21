#ifndef				CLIENTMANAGER_HH_
# define			CLIENTMANAGER_HH_

# include			<map>
# include			<string>

class				Client
{

};

class				ClientManager
{
private:
  std::map<std::string, Client *>	mapClient;

public:
  ClientManager();
  ~ClientManager();

  bool				addClient(const std::string &, Client *);
  bool				removeClient(const std::string &);
  Client*			getClient(const std::string &);
  bool				findClient(const std::string &);
};

#endif
