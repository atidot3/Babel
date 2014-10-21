#ifndef			SERVER_HH_
# define		SERVER_HH_

# define		PORT_SERVER	(4242)
class			Server
{
private:
  ISocket		*sock;
  ClientManager		clients;
  bool			running;

public:
  Server();
  ~Server();
  void			run();
  void			stop();
};

#endif
