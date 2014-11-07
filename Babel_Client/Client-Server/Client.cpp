#include <sstream>
#include <vector>
#include <string>
#include "Client.hpp"
#include "time.h"

Client::Client(int port) : running(false)
{
	socket = new AbstractSocket(port);
}

Client::~Client()
{
	delete socket;
}

void		Client::stop()
{
    running = false;
}

void		Client::update()
{

}

void	Client::getupdate()
{

}

void		Client::getIP()
{
	return;
}
void		Client::run()
{
	string	buff, ip;
    srand(time(NULL));
	try
	{
		running = true;
		//socket->send("salut", "127.0.0.1", SERVER_PORT);
		Struct_Proto t;

	    if (strcmp(t.Buffer, WELCOME) == 0)
		{

			memset(&t, 0, sizeof(t));
			t.audio = 1;
			strcpy_s(t.ip,"127.0.0.1");
			strcpy_s(t.Buffer, "Atidote");
			t.EnumId = 2;
			socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
			memset(&t, 0, sizeof(t));
			socket->recvFromSomeone(ip, SERVER_PORT, &t);
			
			cout << "New client " << t.Buffer << endl;

			t.audio = 1;
			strcpy_s(t.ip,"127.0.0.1");
			strcpy_s(t.Buffer, "Timi");
			t.EnumId = 4;
			strcpy_s(t.myPseudo, "Atidote");
			socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
			memset(&t, 0, sizeof(t));
			socket->recvFromSomeone(ip, SERVER_PORT, &t);
			
			cout << "Adding client " << t.Buffer << endl;

			t.audio = 1;
			strcpy_s(t.ip,"127.0.0.1");
			strcpy_s(t.Buffer, "Yolo");
			t.EnumId = 5;
			strcpy_s(t.myPseudo, "Atidote");
			socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
			memset(&t, 0, sizeof(t));
			socket->recvFromSomeone(ip, SERVER_PORT, &t);
			
			cout << "Removing client " << t.Buffer << endl;

			memset(&t, 0, sizeof(t));
			t.audio = 1;
			strcpy_s(t.ip,"127.0.0.1");
			strcpy_s(t.Buffer, "Atidote");
			t.EnumId = 2;
			socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
			socket->recvFromSomeone(ip, SERVER_PORT, &t);

			memset(&t, 0, sizeof(t));
			t.audio = 1;
			strcpy_s(t.ip,"127.0.0.1");
			strcpy_s(t.Buffer, "Atidote");
			t.EnumId = 9;
			socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);

			cout << "Disconnect" << endl;

			memset(&t, 0, sizeof(t));
			t.audio = 1;
			strcpy_s(t.ip,"127.0.0.1");
			strcpy_s(t.Buffer, "salut");
			t.EnumId = 1;
			socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
			socket->recvFromSomeone(ip, SERVER_PORT, &t);

			memset(&t, 0, sizeof(t));
			t.audio = 1;
			strcpy_s(t.ip,"127.0.0.1");
			strcpy_s(t.Buffer, "Atidote");
			t.EnumId = 2;
			socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
			socket->recvFromSomeone(ip, SERVER_PORT, &t);

			memset(&t, 0, sizeof(t));
			while (running == true)
			{
				
			}
	    }
	}
	catch (std::exception *e)
	{
        cerr << e->what() << endl;
        delete e;
        Sleep(20000);
    }
}

bool 	Client::connectToServer()
{
}

bool 	Client::authToServer()
{
	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, "Atidote");
	t.EnumId = AUTH;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	memset(&t, 0, sizeof(t));
	socket->recvFromSomeone(ip, SERVER_PORT, &t);
	if (strcmp(t.Buffer, "ok") != 0)
		return (false);
	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, "127.0.0.1");
	t.EnumId = AUTH;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	memset(&t, 0, sizeof(t));
	socket->recvFromSomeone(ip, SERVER_PORT, &t);
	if (strcmp(t.Buffer, "ok") != 0)
		return (false);
	return (true);
}

bool 	Client::getContactList()
{
	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, "");
	t.EnumId = CONTACT_LIST;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	memset(&t, 0, sizeof(t));
	socket->recvFromSomeone(ip, SERVER_PORT, &t);
	if (t.Buffer == NULL)
		return (false);
	return (true);
}

bool 	Client::addContact(char *contact)
{
	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, contact);
	t.EnumId = CONTACT_ADD;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	memset(&t, 0, sizeof(t));
	socket->recvFromSomeone(ip, SERVER_PORT, &t);
	if (strcmp(t.Buffer, "ok") != 0)
		return (false);
	return (true);
}

bool 	Client::suppressContact(char *contact)
{
	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, contact);
	t.EnumId = CONTACT_REMOVE;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	memset(&t, 0, sizeof(t));
	socket->recvFromSomeone(ip, SERVER_PORT, &t);
	if (strcmp(t.Buffer, "ok") != 0)
		return (false);
	return (true);
}

bool 	Client::callContact(char *contact)
{
	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, contact);
	t.EnumId = CONTACT_TO_CALL;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	memset(&t, 0, sizeof(t));
	socket->recvFromSomeone(ip, SERVER_PORT, &t);
	if (strcmp(t.Buffer, "ok") != 0)
		return (false);
	return (true);
}

bool	Client::acceptCall(char *contact)
{
/*	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, "");
	t.EnumId = CONTACT_CALL_ME;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	memset(&t, 0, sizeof(t));
	socket->recvFromSomeone(ip, SERVER_PORT, &t);
	if (strcmp(t.Buffer, "ok") != 0)
		return (false);
	return (true);*/
}

bool 	Client::hangUpCall()
{
	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, "");
	t.EnumId = CONTACT_CALL_REFUSE;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	memset(&t, 0, sizeof(t));
	socket->recvFromSomeone(ip, SERVER_PORT, &t);
	if (strcmp(t.Buffer, "ok") != 0)
		return (false);
	return (true);
}

bool 	Client::disconnectFromServer()
{
	memset(&t, 0, sizeof(t));
	strcpy_s(t.Buffer, contact);
	t.EnumId = DISCONNECT;
	socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	return (true);
}

bool	Client::recv_socket(string &data)
{
	data = socket->recv(100, &adresse);
	parser(data);
	return (true);
}

bool	Client::send_socket(string &data) const
{
	string buffer;
	socket->send(data, adresse, SERVER_PORT);
	return (true);
}

 // NE MARCHE PAS A L'INTERIEUR DE L'INSTANCE CLIENT :(
void	str_split(std::list <string>& dst, const std::string& src, char sep)
{
    std::list < char > buffer;
     
    for(std::size_t i(0); i < src.size(); ++i)
	{
        if(src[i] == sep)
            dst.push_back(std::string(buffer.begin(), buffer.end())),
            buffer.clear();
        else
            buffer.push_back(src[i]);
	}
	list<string>::iterator p = dst.begin();
	while(p != dst.end())
	{
		cout << *p << endl;
		p++;
	}

}

void	Client::parse_all_data(const char *item, string &data) const
{
    int totalItem = sizeof(Opt) / NBR_OPT; //nombre objet +1
	int	pos;
	std::list<string> ma_liste; 
	string n_item;
	if (data.empty())
		return;
	str_split(ma_liste, data, ':');

/*    for (int i = 0; i < totalItem; i++)
	{
		if ((pos = data.find(Opt[i])))
		{
			cout << Opt[i] << endl;
 Parse item comme identifiant et récupère les données
à intégrer sur la map pour la SFML 
		}
	}*/
} 
void	Client::parser(string &data) const
{
    int totalItem = sizeof(Type) / NBR_ITEM; //nombre objet +1
	if (data.empty())
		return;
    for (int i = 0; i < totalItem; i++)
	{
		if (data.find(Type[i]))
		{
			parse_all_data(Type[i], data);
			return;
		}
	}
	cout << ERROR_INSTRUCTION;
}
int	main()
{
	srand(43);
	try 
	{
		Client	clie;
		clie.run();
    } 
	catch (std::exception* e)
	{
        std::cerr << e->what() << std::endl;
        delete e;
    }
    return 0;
}