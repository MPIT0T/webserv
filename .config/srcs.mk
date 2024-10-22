# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:46:19 by mpitot            #+#    #+#              #
#    Updated: 2024/10/21 17:31:07 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Sources ******************************************************************** #
SRCS		=	$(MAIN)		\
				$(S_CLASS)


SRC_MAIN	=	main.cpp

SRC_SOCK	=	sockets.cpp	\



DIR_MAIN	=	./
DIR_SOCK	=	sockets/



MAIN		=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))
SOCK		=	$(addprefix $(DIR_SOCK), $(SRC_SOCK))

# Classes ******************************************************************** #
SRC_CLASS	=	Socket.cpp
HEAD_CLASS	=	Socket.hpp

DIR_CLASS	=	Classes/

S_CLASS		=	$(addprefix $(DIR_CLASS), $(SRC_CLASS))
H_CLASS		=	$(addprefix $(DIR_CLASS), $(HEAD_CLASS))

# Headers ******************************************************************** #
HEADERS		=	$(HEAD) $(H_CLASS)

HEAD		=	$(addprefix $(DIR_HEAD), $(SRC_HEAD))

SRC_HEAD	=

DIR_HEAD	=	includes/
