# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:46:19 by mpitot            #+#    #+#              #
#    Updated: 2024/10/30 16:20:14 by mbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Sources ******************************************************************** #

SRCS			=	$(MAIN)			\
					$(SOCK)			\
					$(ANSWER)		\
					$(PARSING)		\
					$(SERVER)		\
					$(RMETHODS)		\
					$(MANAGE_ARGS)	\
					$(UTILS)		\
					$(CGI)			\
					$(LOGGER)

SRC_MAIN		=	main.cpp
SRC_SOCK		=	Socket.cpp		\
					ClientInfo.cpp
SRC_PARSING 	=	Request.cpp
SRC_MANAGE_ARGS	=	ManageArgs.cpp	\
					Listen.cpp		\
					Route.cpp
SRC_SERVER		=	Server.cpp
SRC_ANSWER		=	SendResponse.cpp
SRC_RMETHODS	=	PostMethod.cpp
SRC_UTILS		=	utils.cpp
SRC_LOGGER		=	Logger.cpp
SRC_CGI			=	CGI.cpp

MAIN			=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))
SOCK			=	$(addprefix $(DIR_SOCK), $(SRC_SOCK))
PARSING			=	$(addprefix $(DIR_PARSING), $(SRC_PARSING))
MANAGE_ARGS		=	$(addprefix $(DIR_MANAGE_ARGS), $(SRC_MANAGE_ARGS))
SERVER			=	$(addprefix $(DIR_SERVER), $(SRC_SERVER))
ANSWER			=	$(addprefix $(DIR_ANSWER), $(SRC_ANSWER))
RMETHODS		=	$(addprefix $(DIR_RMETHODS), $(SRC_RMETHODS))
UTILS			=	$(addprefix $(DIR_UTILS), $(SRC_UTILS))
LOGGER			=	$(addprefix $(DIR_LOGGER), $(SRC_LOGGER))
CGI				=	$(addprefix $(DIR_CGI), $(SRC_CGI))

# Directories **************************************************************** #
SRC_D			=	srcs/
DIR_MAIN		=
DIR_SOCK		=	sockets/
DIR_PARSING 	=	parsing/
DIR_MANAGE_ARGS =	manage_args/
DIR_SERVER		=	server/
DIR_ANSWER		=	sendResponse/
DIR_RMETHODS	=	requestMethods/
DIR_UTILS		=	utils/
DIR_LOGGER		=	logger/
DIR_CGI			=	CGI/

# Headers ******************************************************************** #
HEAD			=	-Iincludes						\
					-I$(SRC_D)$(DIR_SOCK)			\
					-I$(SRC_D)$(DIR_PARSING)		\
					-I$(SRC_D)$(DIR_MANAGE_ARGS)	\
					-I$(SRC_D)$(DIR_SERVER)			\
					-I$(SRC_D)$(DIR_ANSWER)			\
					-I$(SRC_D)$(DIR_RMETHODS)		\
					-I$(SRC_D)$(DIR_UTILS)			\
					-I$(SRC_D)$(DIR_LOGGER)
					-I$(SRC_D)$(DIR_CGI)
