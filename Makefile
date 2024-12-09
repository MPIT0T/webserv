# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/14 10:00:31 by tmatis            #+#    #+#              #
#    Updated: 2024/11/05 15:40:04 by gberthol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .config/srcs.mk
include .config/display.mk
include .config/colors.mk

OBJS	=	$(SRCS:%.cpp=${OBJ_D}%.o)
SRC_D	=	srcs/
OBJ_D	=	.objs/
NAME	=	webserv
CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3
DFLAGS	=	-MMD -MF $(@:.o=.d)

AUTHORS	=	mpitot, gberthol, mbrousse
DEBUT	=	21/10/2024
FIN		=	...

all		:	header .internal_separate1 ${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.cpp Makefile
	@$(call print_progress,$<)
	@${CC} ${CFLAGS} ${DFLAGS} ${HEAD} -c $< -o $@
	@$(call update_progress,$<)

-include $(OBJS:.o=.d)
${NAME}	:	${OBJ_D} ${OBJS}
	@$(call print_progress,$(NAME))
	@${CC} ${CFLAGS} ${OBJS} ${HEAD} -o ${NAME}
	@$(eval CHANGED=1)
	@$(call erase)
	@$(call done_and_dusted,$(NAME))

${OBJ_D}:
	@mkdir -p ${OBJ_D}
	@mkdir -p ${OBJ_D}/sockets
	@mkdir -p ${OBJ_D}/sendResponse
	@mkdir -p ${OBJ_D}/manage_args
	@mkdir -p ${OBJ_D}/server
	@mkdir -p ${OBJ_D}/requestMethods
	@mkdir -p ${OBJ_D}/utils
	@mkdir -p ${OBJ_D}/CGI
	@mkdir -p ${OBJ_D}/logger
	@mkdir -p ${OBJ_D}/exchange


clean	:
	@echo "Cleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"

fclean	:
	@echo "F***ing-Cleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"
	@rm -f ${NAME}
	@echo "$(WHITE)[$(RED)$(NAME)$(WHITE)] $(RED)deleted.$(DEFAULT)"

header:
	@printf "$(GREEN_B) _       __     __   $(WHITE_B)_____                \n"
	@printf "$(GREEN_B)| |     / /__  / /_ $(WHITE_B)/ ___/___  ______   __\n"
	@printf "$(GREEN_B)| | /| / / _ \/ __ \\\\$(WHITE_B)\\\\__ \/ _ \/ ___/ | / /\n"
	@printf "$(GREEN_B)| |/ |/ /  __/ /_/ /$(WHITE_B)__/ /  __/ /   | |/ / \n"
	@printf "$(GREEN_B)|__/|__/\___/_.___/$(WHITE_B)____/\___/_/    |___/  \n"
	@echo
	@printf "%b" "$(GREEN_B)Name:		$(WHITE)$(NAME)\n"
	@printf "%b" "$(GREEN_B)Authors:	$(WHITE)$(AUTHORS)\n"
	@printf "%b" "$(GREEN_B)Date: 		$(WHITE)$(DEBUT) $(WHITE_B)-> $(WHITE)$(FIN)\n$(NO_COLOR)"
	@printf "%b" "$(GREEN_B)CC: 		$(WHITE)$(CC)\n$(NO_COLOR)"
	@printf "%b" "$(GREEN_B)Flags: 		$(WHITE)$(CFLAGS)\n$(NO_COLOR)"

leak: all .internal_separate3
	@echo "$(MAGENTA)Valgrind $(WHITE)~ $(YELLOW)Flags:$(DEFAULT)"
	@echo "   $(YELLOW)-$(DEFAULT)Show Leak Kinds"
	@echo "   $(YELLOW)-$(DEFAULT)Track FDs"
	@echo "   $(YELLOW)-$(DEFAULT)Show Mismatched Frees"
	@echo "   $(YELLOW)-$(DEFAULT)Read Variable Information"
	@echo "   $(YELLOW)-$(DEFAULT)Leak check"
	@$(call separator)
	@valgrind		--show-leak-kinds=all		\
					--track-fds=yes 			\
					--show-mismatched-frees=yes	\
					--read-var-info=yes			\
					--leak-check=full			\
					./$(NAME)

re		:	header .internal_separate1 fclean .internal_separate2 ${NAME}

.PHONY	:	all clean fclean re leak

.NOTPARALLEL all:
	@if [ $(CHANGED) -eq 0 ]; then \
		echo "$(YELLOW)Nothing to be done for $(WHITE)[$(CYAN)$(NAME)$(WHITE)].$(DEFAULT)"; \
	fi

.internal_announce	:
	@echo "$(YELLOW)Compiling $(WHITE)[$(CYAN)${NAME}$(WHITE)]...$(DEFAULT)"
