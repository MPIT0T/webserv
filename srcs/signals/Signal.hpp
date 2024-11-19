/* ***************** */
/*      WebServ      */
/* ***************** */

#ifndef SIGNAL_HPP
# define SIGNAL_HPP

# include <map>
#include <vector>

class Signal
{
public:
/* Constructors */
	Signal();
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
