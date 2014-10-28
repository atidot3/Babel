#ifndef SERVER
# define SERVER

#include <list>
#include <string>
#include <iostream>
#include <map>
#include "Include\log.h"
#include "Include\Protocole.h"
#include "Include\iSocket.h"
#include "Include\Client.h"

#define WELCOME "salut"
using namespace std;

class Server
{
public:
	Server(int port = SERVER_PORT);
	~Server();
	void		run();
	void		stop();
	ISocket		*socket;
	bool	AddUser(const char* UserID, Client* newUser);
	void	RemoveUser(const char* UserID);
	bool	FindUser(const char* UserID);
	Client*	GetUserSession(const char* UserID);
private:
	typedef std::map<string, Client*> USERLIST;
	typedef USERLIST::value_type USERVAL;
	typedef USERLIST::iterator USERIT;
	USERLIST	m_userList;
	Protocole	*proto;
	bool		running;
};

#endif