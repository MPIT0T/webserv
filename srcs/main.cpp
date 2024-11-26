/* ***************** */
/*      WebServ      */
/* ***************** */

#include "ManageArgs.hpp"
#include "Server.hpp"
#include <cstdlib>

int main(int argc, char *argv[], char *env[])
{
	Server server;
	server.setEnv(env);
	ManageArgs args(argc, argv);
	Logger log( env );
	server.log = log;


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
		server.log.log( Logger::ERROR, e.what());
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
