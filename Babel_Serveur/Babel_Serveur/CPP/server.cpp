#include "Include\server.h"
#include "time.h"
#include "stdlib.h"

Server::Server(int port) : running(false)
{
	socket = new AbstractSocket(port);
	proto = new Protocole();
}

Server::~Server()
{
	delete socket;
}

void		Server::stop()
{
    running = false;
}
bool		Server::AddUser(const char* UserID, Client* newUser)
{
	if( false == m_userList.insert( USERVAL(string(UserID), newUser)).second )
	{
		return false;
	}
	return true;		
}
void		Server::RemoveUser(const char* UserID)
{
	m_userList.erase( string(UserID) );
}
bool		Server::FindUser(const char* UserID)
{
	USERIT it = m_userList.find(string(UserID));
	if( it == m_userList.end() )
		return false;
	return true;
}
Client*		Server::GetUserSession(const char* UserID)
{
	USERIT it = m_userList.find(string(UserID));
	if( it == m_userList.end() )
		return NULL;
	return it->second;
}
void		Server::run()
{
	string	buff, ip;
    srand(time(NULL));
	Logger::Instance()->log(0, "----------------Server Started...-------------\n");
    try
	{
		running = true;
		while (running == true)
		{
			Struct_Proto* t = new Struct_Proto();
			socket->recvFromSomeone(ip, 100, t);
			printf("audio: %d, enum: %d, string: %s\n", t->audio, t->EnumId, t->Buffer);
			proto->Protocole_to_call(t->EnumId, t->Buffer);
			delete t;
		}
	}
	catch (std::exception *e)
	{
        cerr << e->what() << endl;
        delete e;
    }
}