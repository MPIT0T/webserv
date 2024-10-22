# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:46:19 by mpitot            #+#    #+#              #
#    Updated: 2024/10/22 14:25:30 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Sources ******************************************************************** #
SRCS		=	$(MAIN)			\
				$(SOCK)

SRC_MAIN	=	main.cpp
SRC_SOCK	=	Socket.cpp

MAIN		=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))
SOCK		=	$(addprefix $(DIR_SOCK), $(SRC_SOCK))

# Directories **************************************************************** #
SRC_D		=	srcs/
DIR_MAIN	=
DIR_SOCK	=	sockets/

# Headers ******************************************************************** #
HEAD		=	-Iincludes -I$(SRC_D)$(DIR_SOCK)