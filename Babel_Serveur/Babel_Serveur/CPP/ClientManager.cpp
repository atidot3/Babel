#include		"Include/ClientManager.hh"

ClientManager::ClientManager()
{
}

ClientManager::~ClientManager()
{
  std::map<std::string, Client *>::iterator	it;

  it = mapClient.begin();
  while (it != mapClient.end())
    {
      mapClient.erase(it);
      it = mapClient.begin();
    }
}

bool			ClientManager::addClient(const std::string &pseudo, Client *client)
{
  mapClient[pseudo] = client;
  return (true);
}

bool			ClientManager::removeClient(const std::string &pseudo)
{
  std::map<
    std::string,
    Client *>::iterator	it;

  it = mapClient.begin();
  while (it != mapClient.end() && it->first != pseudo)
    ++it;
  if (it == mapClient.end())
    return (false);
  mapClient.erase(it);
  return (true);
}

Client*			ClientManager::getClient(const std::string &pseudo)
{
  std::map<
    std::string,
    Client *>::iterator	it;

  it = mapClient.begin();
  while (it != mapClient.end() && it->first != pseudo)
    ++it;
  if (it == mapClient.end())
    return (NULL);
  return (it->second);
}

bool			ClientManager::findClient(const std::string &pseudo)
{
  std::map<
    std::string,
    Client *>::iterator	it;

  it = mapClient.begin();
  while (it != mapClient.end() && it->first != pseudo)
    ++it;
  if (it == mapClient.end())
    return (false);
  return (true);
}
