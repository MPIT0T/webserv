# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:46:19 by mpitot            #+#    #+#              #
#    Updated: 2024/10/21 15:51:04 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Sources ******************************************************************** #
SRCS		=	$(MAIN)			\
				$(SOCK)			\
				$(PARSING)

SRC_MAIN	=	main.cpp
SRC_SOCK	=	Socket.cpp		\
				ClientInfo.cpp
SRC_PARSING =	Request.cpp		\
				Header.cpp

MAIN		=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))
SOCK		=	$(addprefix $(DIR_SOCK), $(SRC_SOCK))
PARSING		=	$(addprefix $(DIR_PARSING), $(SRC_PARSING))
# Directories **************************************************************** #
SRC_D		=	srcs/
DIR_MAIN	=
DIR_SOCK	=	sockets/
DIR_PARSING =	parsing/

# Headers ******************************************************************** #
HEAD		=	-Iincludes -I$(SRC_D)$(DIR_SOCK) -I$(SRC_D)$(DIR_PARSING)