#ifndef		SELECT_HH_
# define	SELECT_HH_

# include	"Server.hh"
# include	<sys/select.h>
# include	<sys/time.h>
# include	<sys/types.h>

class		Select
{
private:
  TYPE		cs;
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
  void          sendThings(Server *);
  void		recvThings(Server *);
};

#endif
