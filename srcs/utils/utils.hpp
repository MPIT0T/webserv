/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:30:34 by mbrousse          #+#    #+#             */
/*   Updated: 2024/10/30 16:29:54 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "Listen.hpp"

std::string readFileContent(const std::string& filePath);
std::vector<std::string> tokenizeConfig(const std::string& content);
void printTokens(const std::vector<std::string>& tokens);
void printListen(const std::vector<Listen>& listen);

#endif // UTILS_HPP