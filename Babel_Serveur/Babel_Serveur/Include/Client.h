#ifndef CLIENT
# define CLIENT

class Client
{
public:
	Client(string Username);
	~Client(){};
private:
	string	Name;
	typedef std::list<string> CONTACTLIST;
	typedef CONTACTLIST::value_type CONTACTVAL;
	typedef CONTACTLIST::iterator CONTACTIT;
};

#endif