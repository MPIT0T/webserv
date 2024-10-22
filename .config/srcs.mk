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

SRCS		=	$(MAIN)		\
				$(PARSING)	\
#				$(UTILS)	\
#				$(ERROR)



SRC_MAIN	=	main.cpp
SRC_PARSING =	Request.cpp		\
				Header.cpp
SRC_UTILS	=	utils.example
SRC_ERROR	=	error.example


DIR_MAIN	=	./
DIR_UTILS	=	utils/
DIR_PARSING =	parsing/
DIR_ERROR	=	error/



MAIN		=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))
ERROR		=	$(addprefix $(DIR_ERROR), $(SRC_ERROR))
UTILS		=	$(addprefix $(DIR_UTILS), $(SRC_UTILS))
PARSING		=	$(addprefix $(DIR_PARSING), $(SRC_PARSING))

# **************************************************************************** #

HEAD		=	$(addprefix $(DIR_HEAD), $(HEADERS))

HEADERS		=	[example1.h]	\
				[example2.h]	\
				[example3.h]

DIR_HEAD	=	includes/
