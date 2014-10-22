#include <sstream>
#include <vector>
#include <string>
#include "client.hpp"
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
		t.audio = 9000;
		strcpy(t.Buffer, "Je test ma race");
		t.EnumId = 7000;
		socket->sendToSomeone(&t, "127.0.0.1", SERVER_PORT);
	    buff = socket->recv(100, &adresse);
	    if (buff == WELCOME)
	    {
	        cout << "New client " << adresse << endl;
			while (running == true)
			{
				recv_socket(data);
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
