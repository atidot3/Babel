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
			Struct_Proto* t = socket->recvFromSomeone(ip, 100);
			printf("audio: %d, enum: %d, string: %s\n", t->audio, t->EnumId, t->Buffer);
			cout << t->audio << " " << t->Buffer << " " << t->EnumId << endl;
			//buff = socket->recv(100, &ip);
			cout << "Buff received" << ip << endl;
			if ((this->FindUser(ip.c_str())) == true)
			{
				cout << "client already connected, exiting..." << ip << endl;
				Logger::Instance()->log(1, "client already connected:" + ip + ", exiting...\n");
				buff = "";
		    }
			/*socket->send("salut", ip, CLIENT_PORT);
		    if (buff == WELCOME)
		    {
				Logger::Instance()->log(0, "Client connected: " + ip + ".\n");
				cout << "New client " << ip.c_str() << endl;
				Client* NewOne = new Client(ip.c_str());
				this->AddUser(ip.c_str(), NewOne);
			}*/
		}
	}
	catch (std::exception *e)
	{
        cerr << e->what() << endl;
        delete e;
    }
}