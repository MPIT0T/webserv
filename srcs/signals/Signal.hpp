/* ***************** */
/*      WebServ      */
/* ***************** */

#ifndef SIGNAL_HPP
# define SIGNAL_HPP

#include <map>
#include <vector>
#include <csignal>
#include "Server.hpp"

class Signal
{
public:
/* Constructors */
	Signal( void );
	Signal( Server *server );
	Signal(const Signal &src);
	~Signal();

/* Operators */
	Signal &operator=(const Signal &src);
	
/* Methods */
	int		setSignal(int sig);
private:
	std::map<int, char *>	_signals;
};



#endif //SIGNAL_HPP
