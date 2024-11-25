#include "ManageArgs.hpp"

ManageArgs::ManageArgs( int argc, char *argv[] ) : _argc(argc), _argv(argv)
{
    return ;
}

ManageArgs::ManageArgs( const ManageArgs &src )
{
    *this = src;
    return ;
}

ManageArgs &ManageArgs::operator=( const ManageArgs &src )
{
    if (this != &src)
    {
        this->_argc = src._argc;
        this->_argv = src._argv;
    }
    return *this;
}

ManageArgs::~ManageArgs()
{
    return ;
}

int ManageArgs::getArgc( void ) const
{
    return this->_argc;
}

char **ManageArgs::getArgv( void ) const
{
    return this->_argv;
}

bool ManageArgs::checkArgs( void ) const
{
    if (this->_argc < 2)
    {
        std::cerr << "Usage: " << this->_argv[0] << " [configuration file]" << std::endl;
        return false;
    }
    return true;
}