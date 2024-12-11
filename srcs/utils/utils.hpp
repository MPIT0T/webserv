/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:30:34 by mbrousse          #+#    #+#             */
/*   Updated: 2024/11/05 13:47:23 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "Listen.hpp"

std::string 	readFileContent(const std::string& filePath);
std::string     errorPage(int code);
std::string		toString(int number);
std::string     getRouteAccess(const std::string &routeAccess, const std::map<std::string, Route> &routes);

#endif // UTILS_HPP