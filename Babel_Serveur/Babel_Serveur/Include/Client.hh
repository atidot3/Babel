#ifndef		CLIENT_HH_
# define	CLIENT_HH_

# include	"Include/FileContact.hh"
# include	<string>
# include	"Include/ISocket.hh"

class		Client
{
private:
  bool		_busy;
  int		_id;
  ISocket*	_sock;
  std::string	_ip;
  std::string	_pseudo;
  FileContact	*_contacts;
  Proto_Struct	*_sending;
  Proto_Struct	*_receiving;

public:
  Client(int);
  Client(ISocket *, int);
  Client(ISocket *, const std::string &, int);
  Client(ISocket *, const std::string &, const std::string &, int);
  ~Client();

  ISocket*	getSock() const;
  std::string	getIp() const;
  std::string	getPseudo() const;
  FileContact	*getContacts() const;
  Proto_Struct	*getSending() const;
  Proto_Struct	*getReceiving() const;
  int		getId() const;
  void		setSock(ISocket *);
  void		setIp(const std::string &);
  void		setPseudo(const std::string &);
  void		setSending(Proto_Struct *);
  void		setReceiving(Proto_Struct *);
  void		setId(int);
  bool		isBusy() const;
  void		setBusy(bool);
};

#endif
