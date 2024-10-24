/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ManageArgs.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:15:47 by mbrousse          #+#    #+#             */
/*   Updated: 2024/10/24 10:14:23 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGEARGS_HPP
#define MANAGEARGS_HPP

#include <iostream>
class ManageArgs{
private:
    ManageArgs( void );
    int _argc;
    char **_argv;
    
public:
    ManageArgs( int argc, char *argv[] );
    ManageArgs( const ManageArgs &src );
    ManageArgs &operator=( const ManageArgs &src );
    
    ~ManageArgs();
    
    int getArgc( void ) const;
    char **getArgv( void ) const;
    bool checkArgs( void ) const;
};

#endif // MANAGEARGS_HPP