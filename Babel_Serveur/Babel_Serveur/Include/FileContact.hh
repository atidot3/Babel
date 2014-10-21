#ifndef			FILECONTACT_HH_
# define		FILECONTACT_HH_

# include		<fstream>
# include		<list>

class			FileContact
{
  std::string		_pseudo;
  std::list<
    std::string>	_list;

public:
  FileContact(const std::string &);
  ~FileContact();
  bool			find(const std::string &);
  bool			add(const std::string &);
  bool			erase(const std::string &);
  bool			fillList();
  std::list
  <std::string>		getList();
};

#endif
