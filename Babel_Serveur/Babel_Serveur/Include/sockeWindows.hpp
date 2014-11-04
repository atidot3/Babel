#ifndef		SOCKETWINDOWS_HH_
# define	SOCKETWINDOWS_HH_

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include	<cstring>
#include	<sys/types.h>
#include	<io.h>
#include	<windows.h>
#include	<iostream>
#include	<string>

class		socketWindows : public ISocket
{
private:
  SOCKET	sock;

public:
  socketWindows(): ISocket()
  {
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2,2), &WSAData);
    
	if ((sock = ::socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        std::cout << "Could not create client socket" << std::endl;
  }

  socketWindows(int fd)
  {
    sock = fd;
  }

  ~socketWindows()
  {
    ::_close(sock);
  }

  virtual bool	bind()
  {
    struct sockaddr_in	sin;

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = INADDR_ANY;
    if (::bind(sock, (SOCKADDR *)(&sin), sizeof(sin)) == -1)
	{
		std::cout << "BIND ERROR" << std::endl;
		delete(this);
	}
    return (0);
  }

  virtual bool	listen()
  {
    ::listen(sock, 42);
    return (true);
  }

  virtual void	close()
  {
    //delete(this);
  }

  virtual ISocket*	accept()
  {
	ISocket* clientSocket;
    SOCKET newSock;
    SOCKADDR_IN csin;
    int csinSize;

    if ((newSock = ::accept(sock, (SOCKADDR *)&csin, &csinSize)) == INVALID_SOCKET)
    {
		std::cout << "NULL" << std::endl;
        return NULL;
    }
	clientSocket = new socketWindows(newSock);
	return clientSocket;
  }

  virtual int	realSock()
  {
    return (sock);
  }

  virtual void		sendToSomeone(Proto_Struct *proto, const std::string &ip, int port)
  {
    /*if ((write(sock, proto, sizeof(Proto_Struct))) == -1)
		std::cout << "WRITE ERROR" << std::endl;*/
	SOCKADDR_IN toSin;
    toSin.sin_addr.s_addr = inet_addr(ip.c_str());
    toSin.sin_family = AF_INET;
    toSin.sin_port	= htons(port);
	::sendto(sock, (char*)proto, sizeof(Proto_Struct), 0, (SOCKADDR *)&toSin, sizeof(toSin));
  }
  
  virtual void		recvFromSomeone(const std::string &ip, int port, Proto_Struct *proto)
  {
    /*if ((read(sock, proto, sizeof(Proto_Struct))) == -1)
		std::cout << "READ ERROR" << std::endl;*/
	  SOCKADDR_IN fromSin;
      int fromLen = sizeof(fromSin);
	  ::recvfrom(sock, (char*)proto, sizeof(Proto_Struct), 0, (SOCKADDR *)&fromSin, &fromLen);
  }
};
#ifdef WIN32
typedef socketWindows AbstractSocket;
#endif
#endif
