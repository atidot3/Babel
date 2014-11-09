#ifndef		BABELEXCEPTION_HPP
# define	BABELEXCEPTION_HPP

class		BabelException : public std::exception
{
private:
  std::string _msg;

public:
  BabelException(const char *msg)
  {
    _msg = msg;
  }
  virtual ~BabelException() throw()
  {
  }

  virtual const char* what() const throw()
  {
    return (_msg.c_str());
  }

};

#endif
