/* ***************** */
/*      WebServ      */
/* ***************** */

#include "ManageArgs.hpp"
#include "Server.hpp"
#include <cstdlib>

Server *g_server;

int main(int argc, char *argv[])
{
	Server		server;
	ManageArgs	args(argc, argv);

	g_server = &server;
	if (!args.checkArgs())
		return (EXIT_FAILURE);
	try
	{
		if(server.parseConfigFile(args.getArgv()[1]) == false)
			return (EXIT_FAILURE);
		
		server.init();
		server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
