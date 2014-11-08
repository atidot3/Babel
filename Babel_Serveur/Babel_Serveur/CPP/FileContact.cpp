#include		"Include/FileContact.hh"
#include		<string>
#include		<iostream>
#include		<vector>

FileContact::FileContact(const std::string &pseudo)
{
  std::ofstream		file;

  this->_user = pseudo;
  this->_pseudo = "accounts/" + pseudo;

  if (this->checkExistence(pseudo) == false)
    {
      file.open(_pseudo.c_str(), std::ios::out);
      file.close();
    }
}

FileContact::~FileContact()
{
}

bool			FileContact::find(const std::string &contact)
{
  std::ifstream		file(_pseudo.c_str(), std::ios::in);
  std::string		line;

  if (file)
    {
      while (getline(file, line))
	{
	  if (line == contact)
	    {
	      file.close();
	      return (true);
	    }
	}
    }
  file.close();
  return (false);
}

bool			FileContact::add(const std::string &contact)
{
  std::ofstream		file;

  std::cout << contact << ", " << this->_user << std::endl;
  if (contact == this->_user)
    return (false);
  if (this->checkExistence(contact) == false)
    return (false);
  if (this->find(contact) == false)
    {
      if (file)
	{
	  std::cout << _pseudo << std::endl;
	  file.open(_pseudo.c_str(), std::ios::out | std::ios::app);
	    file << contact << std::endl;
	  file.close();
	  return (true);
	}
    }
  return (false);
}

bool			FileContact::erase(const std::string &contact)
{
  std::ofstream		file;
  std::list<std::string>::iterator		it;

  if (this->find(contact) == false)
    return (false);
  this->fillList();
  it = _list.begin();
  file.open(_pseudo.c_str(), std::ios::out | std::ios::trunc);
  if (file)
    {
      while (it != _list.end())
	{
	  if (*it != contact)
	    file << *it << std::endl;
	  ++it;
	}
      file.close();
      return (true);
    }
  return (false);
}

bool			FileContact::eraseList()
{
  std::list<std::string>::iterator	it;

  it = _list.begin();
  while (it != _list.end())
    {
      _list.erase(it);
      it = _list.begin();
    }
  return (true);
}

bool			FileContact::fillList()
{
  std::ifstream		file(_pseudo.c_str(), std::ios::in);
  std::string		line;

  if (file)
    {
      while (getline(file, line))
	_list.push_back(line);
      file.close();
      return (true);
    }
  return (false);
}

std::list<std::string>	*FileContact::getList()
{
  eraseList();
  fillList();
  return (&_list);
}

bool			FileContact::checkExistence(const std::string &contact)
{
  std::ifstream		file;
  std::string		line;

  line = "accounts/" + contact;
  file.open(line.c_str(), std::ios::in);
  if (!file)
    return (false);
  file.close();
  return (true);
}
