################################################################################
#                                  Makefile  srcs                              #
################################################################################

FILE_EXTENSION	=	.cpp

SRCS_PATH		=	./srcs

INCLUDE_PATH	=	./srcs

SRCS			=

MAIN			= 	main.cpp

################################################################################
#                                  Makefile  objs                              #
################################################################################

SHELL := /bin/bash

OBJS				= $(addprefix objs/, ${SRCS:$(FILE_EXTENSION)=.o})
OBJ_MAIN			= $(addprefix objs/, ${MAIN:$(FILE_EXTENSION)=.o})
DEPS				= $(addprefix objs/, ${SRCS:$(FILE_EXTENSION)=.d})
DEPS_MAIN			= $(addprefix objs/, ${MAIN:$(FILE_EXTENSION)=.d})
