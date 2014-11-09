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
      {
	wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
	throw std::runtime_error("socket function failed");
      }
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
	wprintf(L"bind function failed with error %d\n", WSAGetLastError());
	if ((closesocket(sock)) == SOCKET_ERROR)
	  {
	    wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
	  }
	throw std::runtime_error("bind function failed");
	WSACleanup();
	delete(this);
	return false;
      }
    return true;
  }

  virtual bool	listen()
  {
    if ((::listen(sock, 42)) == SOCKET_ERROR)
      {
	wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
	if ((closesocket(sock)) == SOCKET_ERROR)
	  {
	    wprintf(L"closesocket function failed with error %d\n", WSAGetLastError());
	  }
	WSACleanup();
	throw std::runtime_error("listen function failed");
	return false;
      }
    return (true);
  }

  virtual void	close()
  {
  }

  virtual ISocket*	accept()
  {
    ISocket* clientSocket;
    SOCKET newSock;
    SOCKADDR_IN csin;
    int csinSize;

    if ((newSock = ::accept(sock, (SOCKADDR *)&csin, &csinSize)) == INVALID_SOCKET)
      {
	wprintf(L"accept function failed with error: %ld\n", WSAGetLastError());
	WSACleanup();
	throw std::runtime_error("accept function failed");
        return NULL;
      }
    clientSocket = new socketWindows(newSock);
    return clientSocket;
  }

  virtual int	realSock()
  {
    return (sock);
  }

  virtual bool		sendToSomeone(Proto_Struct *proto, const std::string &ip, int port)
  {
    SOCKADDR_IN toSin;
    toSin.sin_addr.s_addr = inet_addr(ip.c_str());
    toSin.sin_family = AF_INET;
    toSin.sin_port	= htons(port);
    if ((::sendto(sock, (char*)proto, sizeof(Proto_Struct), 0, (SOCKADDR *)&toSin, sizeof(toSin))) == SOCKET_ERROR)
      {
	wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        if ((closesocket(sock)) == SOCKET_ERROR)
	  {
	    wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
	    WSACleanup();
	    return (false);
	  }
	WSACleanup();
      }
    return (true);
  }
  
  virtual bool		recvFromSomeone(const std::string &ip, int port, Proto_Struct *proto)
  {
    SOCKADDR_IN fromSin;
    int fromLen = sizeof(fromSin);
    if ((::recvfrom(sock, (char*)proto, sizeof(Proto_Struct), 0, (SOCKADDR *)&fromSin, &fromLen)) == SOCKET_ERROR)
      {
	wprintf(L"recvfrom failed with error: %d\n", WSAGetLastError());
	if ((closesocket(sock)) == SOCKET_ERROR)
	  {
	    wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
	    WSACleanup();
	    return (false);
	  }
	WSACleanup();
      }
    return (true);
  }
};
#ifdef WIN32
	typedef socketWindows AbstractSocket;
#endif
#endif
