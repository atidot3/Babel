#ifndef ISOCKET
# define ISOCKET

#include "socketException.hpp"


#define SERVER_PORT 4242
#define CLIENT_PORT 4243
typedef	struct Proto_Struct Struct_Proto;
class ISocket
{
public:
	virtual ~ISocket() {};

	virtual void connect() = 0;
	virtual ISocket* accept() = 0;
	virtual void send(const std::string&, std::string ip = "", int port = 0) = 0;
	virtual void	sendToSomeone(Struct_Proto* stru, std::string ip, int port) = 0;
	virtual	void	recvFromSomeone(std::string ip, int port, Struct_Proto *t)=0;
	virtual std::string recv(int, std::string* ip = NULL) = 0;

private:
	virtual void bind() = 0;
	virtual void listen(int) = 0;
};

class Formater
{
public:
    template <class TYPE>
    static string& pack(string &data, TYPE val) {
        data += string((char *)&val, sizeof(TYPE));
        return data;
    }
    template <class TYPE>
    static TYPE unpack(string &data) {
        TYPE    out;
        out = *((TYPE *)data.c_str());
        data.erase(0, sizeof(TYPE));
        return out;
    }
};

#ifdef _WIN32
    #include "socketWindows.hpp"
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include "sockets/socketUnix.hpp"
#endif

#endif //ISOCKET