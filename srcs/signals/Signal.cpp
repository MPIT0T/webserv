/* ***************** */
/*      WebServ      */
/* ***************** */

#include "Signal.hpp"

Server *g_server;

/* Constructors ************************************************************* */
Signal::Signal() {}

Signal::Signal(Server *server)
{
	g_server = server;
}

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
	delete g_server;
	(void)sig;
	exit(130);
}

int Signal::setSignal(const int sig)
{
	signal(sig, &handleSIGINT);
	return (0);
}
