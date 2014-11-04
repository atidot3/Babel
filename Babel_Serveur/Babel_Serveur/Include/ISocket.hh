#ifndef		ISOCKET_HH_
# define	ISOCKET_HH_

# include	<string>

# ifdef	_WIN32
#  define TYPE SOCKET
# else
#  define  TYPE int
# endif

# define	PORT	4242

  enum			PROTOCOLE_ENUM
    {
      WELCOME = 0,
      AUTH,
      CONTACT_LIST,
      CONTACT_ADD,
      CONTACT_REMOVE,
      CONTACT_CALL_ME,
      CONTACT_TO_CALL,
      SEND_AUDIO,
      DISCONNECT
    };

struct				Struct_proto
{
  PROTOCOLE_ENUM		cmd;
  char			buffer[512];
};

typedef				Struct_proto Proto_Struct;

class		ISocket
{
public:
  virtual bool	bind() = 0;
  virtual bool	listen() = 0;
  virtual void	close() = 0;
  virtual ISocket*	accept() = 0;
  virtual TYPE	realSock() = 0;
  virtual void	sendToSomeone(Proto_Struct *, const std::string &, int ) = 0;
  virtual void	recvFromSomeone(const std::string &, int, Proto_Struct *) = 0;
};

# ifdef	_WIN32
#  include "socketWindows.hpp"
# else
#  include "socketUnix.hpp"
# endif

#endif
