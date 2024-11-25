/* ***************** */
/*      WebServ      */
/* ***************** */

#include "ManageArgs.hpp"
#include "Server.hpp"
#include <cstdlib>

Server *g_server;

int main(int argc, char *argv[], char *env[])
{
	Server server;
	g_server = &server;
	g_server->setEnv(env);
	ManageArgs args(argc, argv);

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
