/*
*
* Client Manager
*
*/

#include "Include\server.h"
#include "Include\Client.h"

Client::Client(string Username)
{
	this->Name = Username;
}
Client::~Client()
{
	CONTACTIT IT = myList.begin();
	while (IT != myList.end())
	{
		myList.erase(IT);
	}
}
Client::CONTACTLIST	Client::getContact()
{
	return this->myList;
}
bool			Client::addClient(const std::string &pseudo)
{
  
}
bool			Client::removeClient(const std::string &pseudo)
{

}
Client*			Client::getClient()
{
	return this;
}
bool			Client::findClient(const std::string &pseudo)
{

}
