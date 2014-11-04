#ifndef		SOCKETUNIX_HH_
# define	SOCKETUNIT_HH_

# include	<cstring>
# include	<unistd.h>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<netdb.h>

class		socketUnix : public ISocket
{
private:
  TYPE		sock;

public:
  socketUnix()
  {
    struct protoent	*pe;

    pe = getprotobyname("TCP");
    sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  }

  socketUnix(int fd)
  {
    sock = fd;
  }

  ~socketUnix()
  {
    ::close(sock);
  }

  virtual bool	bind()
  {
    struct sockaddr_in	sin;

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = INADDR_ANY;
    if (::bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
      delete(this);
    return (0);
  }

  virtual bool	listen()
  {
    ::listen(sock, 42);
    return (true);
  }

  virtual void	close()
  {
    delete(this);
  }

  virtual ISocket*	accept()
  {
    ISocket*		ret;
    int			cs;
    struct sockaddr_in	sin_client;
    int			client_len;

    ret = NULL;
    if ((cs = ::accept(sock, (struct sockaddr *)&sin_client, (socklen_t *)&client_len)) == -1)
      return (NULL);
    ret = new socketUnix(cs);
    return (ret);  
  }

  virtual TYPE		realSock()
  {
    return (sock);
  }

  virtual void		sendToSomeone(Proto_Struct *proto, const std::string &ip, int port)
  {
    write(sock, proto, sizeof(Proto_Struct));
  }
  
  virtual void		recvFromSomeone(const std::string &ip, int port, Proto_Struct *proto)
  {
    read(sock, proto, sizeof(Proto_Struct));
  }
};

#endif
