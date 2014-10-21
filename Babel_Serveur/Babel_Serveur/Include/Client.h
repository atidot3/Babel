#ifndef		CLIENT_HH_
# define	CLIENT_HH_

#include <string>
#include <list>
#include <iostream>
#include <map>

class ISocket;

class Client
{
 private:
	typedef std::list<std::string> CONTACTLIST;
	typedef CONTACTLIST::value_type CONTACTVAL;
	typedef CONTACTLIST::iterator CONTACTIT;

private:
	ISocket		*sock;
	bool		busy;
	bool		called;
	//FileContact	contacts;
	CONTACTLIST	myList;
	std::string	pseudo;
	/* protocol reading */

public:
	Client(std::string Username);
	~Client();
	CONTACTLIST	getContact();
private:
	bool				addContact(const std::string &);
	bool				removeContact(const std::string &);
	std::string			IsAskingConnection();
	ISocket*			acceptConnection(const std::string &);
	bool				isBusy();
	bool				isCalled();
};

#endif
