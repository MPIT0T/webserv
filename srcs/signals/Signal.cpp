/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Signal.hpp"
#include <csignal>

/* Constructors ************************************************************* */
Signal::Signal() {}

Signal::Signal(const Signal &src)
{
	*this = src;
}

Signal::~Signal() {}

/* Operators **************************************************************** */
Signal &Signal::operator=(const Signal &src)
{
	(void) src;
	return (*this);
}

/* Methods ****************************************************************** */

static void	handleSIGINT(int sig)
{
	(void) sig;
}

int Signal::setSignal(const int sig)
{
	signal(sig, &handleSIGINT);
	return (0);
}
