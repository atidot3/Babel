#include <list>
#include <iostream>
#include <map>

#ifndef CLIENT
# define CLIENT

using namespace std;

class Client
{
private:
	typedef std::list<string> CONTACTLIST;
	typedef CONTACTLIST::value_type CONTACTVAL;
	typedef CONTACTLIST::iterator CONTACTIT;
	CONTACTLIST	myList;
public:
	Client(string Username);
	~Client();
	CONTACTLIST	getContact();
private:
	string	Name;
	bool				addClient(const std::string &);
	bool				removeClient(const std::string &);
	Client*				getClient();
	bool				findClient(const std::string &);
};

#endif