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
SRCS			=	$(MAIN)			\
					$(SOCK)			\
					$(ANSWER)		\
					$(PARSING)		\
					$(SERVER)		\
					$(MANAGE_ARGS)

SRC_MAIN		=	main.cpp
SRC_SOCK		=	Socket.cpp		\
					ClientInfo.cpp
SRC_PARSING 	=	Request.cpp		\
					Header.cpp
SRC_MANAGE_ARGS	=	ManageArgs.cpp
SRC_SERVER		=	Server.cpp
SRC_ANSWER		=	SendResponse.cpp

MAIN			=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))
SOCK			=	$(addprefix $(DIR_SOCK), $(SRC_SOCK))
PARSING			=	$(addprefix $(DIR_PARSING), $(SRC_PARSING))
MANAGE_ARGS		=	$(addprefix $(DIR_MANAGE_ARGS), $(SRC_MANAGE_ARGS))
SERVER			=	$(addprefix $(DIR_SERVER), $(SRC_SERVER))
ANSWER			=	$(addprefix $(DIR_ANSWER), $(SRC_ANSWER))

# Directories **************************************************************** #
SRC_D			=	srcs/
DIR_MAIN		=
DIR_SOCK		=	sockets/
DIR_PARSING 	=	parsing/
DIR_MANAGE_ARGS =	manage_args/
DIR_SERVER		=	server/
DIR_ANSWER		=	sendResponse/


# Headers ******************************************************************** #
HEAD			=	-Iincludes						\
					-I$(SRC_D)$(DIR_SOCK)			\
					-I$(SRC_D)$(DIR_PARSING)		\
					-I$(SRC_D)$(DIR_MANAGE_ARGS)	\
					-I$(SRC_D)$(DIR_SERVER)			\
					-I$(SRC_D)$(DIR_ANSWER)