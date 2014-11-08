#ifndef		SELECT_HH_
# define	SELECT_HH_

#include	"Include/Server.hh"
# ifdef	_WIN32
	#include	<WS2tcpip.h>
#else
	#include	<sys/select.h>
	#include	<sys/time.h>
	#include	<sys/types.h>
# endif

class		Select
{
private:
  int		cs;
  fd_set	readfds;
  fd_set	writefds;

private:
  bool		init(Server*);

public:
  Select(Server *);
  ~Select();
  
  int		waitFds(Server *);
  fd_set	getReadFds();
  fd_set	getWriteFds();
  bool		isThereNewClient(Server *);
  void      sendThings(Server *);
  void		recvThings(Server *);
};

#endif
