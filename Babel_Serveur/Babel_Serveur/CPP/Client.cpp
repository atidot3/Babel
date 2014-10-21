/*
*
* Client Manager
*
*/

#include "Include\server.h"
#include "Include\Client.h"

Client::Client(string Username)
{
	this->pseudo = Username;
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
bool			Client::addContact(const std::string &pseudo)
{
  /* contacts.write(pseudo); */
}
bool			Client::removeContact(const std::string &pseudo)
{
  /* contacts.erase(pseudo); */
}

std::string		Client::IsAskingConnection()
{
  /* Entrer dans cette fonction si le client veut demander un appel à quelqu'un

     Récupère le pseudo du contact à appeller
     return le pseudo
  */
}

ISocket*		Client::acceptConnection(const std::string &pseudo)
{
  /* demande au client s'il veut répondre à pseudo

     attends la réponse
     si oui -> return socket
     si non -> return NULL

     si celui qui appelle raccroche avant la réponse -> return NULL
 */
}
bool			Client::isBusy()
{
	return this->busy;
}
bool			Client::isCalled()
{
	return this->called;
}