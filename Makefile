# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/14 10:00:31 by tmatis            #+#    #+#              #
#    Updated: 2024/10/21 15:08:35 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .config/srcs.mk
include .config/config.mk

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME	= webserv
CC 		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
DFLAGS	= -MMD -MF $(@:.o=.d)
AUTHOR	= mpitot, gberthol, mbrousse
DATE	= 21/10/2024

NOVISU 	= 0 # 1 = no progress bar usefull when tty is not available

################################################################################
#                                 Makefile rules                             #
################################################################################

all: header setup $(NAME)
	@rm -rf .files_changed

header:
	@printf "$(GREEN) _       __     __   $(WHITE)_____                \n"
	@printf "$(GREEN)| |     / /__  / /_ $(WHITE)/ ___/___  ______   __\n"
	@printf "$(GREEN)| | /| / / _ \/ __ \\\\$(WHITE)\\\\__ \/ _ \/ ___/ | / /\n"
	@printf "$(GREEN)| |/ |/ /  __/ /_/ /$(WHITE)__/ /  __/ /   | |/ / \n"
	@printf "$(GREEN)|__/|__/\___/_.___/$(WHITE)____/\___/_/    |___/  \n"
	@echo
	@printf "%b" "$(OBJ_COLOR)Name:		$(WHITE_FIN)$(NAME)\n"
	@printf "%b" "$(OBJ_COLOR)Authors:	$(WHITE_FIN)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 		$(WHITE_FIN)$(DATE)\n$(NO_COLOR)"
	@printf "%b" "$(OBJ_COLOR)CC: 		$(WHITE_FIN)$(CC)\n$(NO_COLOR)"
	@printf "%b" "$(OBJ_COLOR)Flags: 		$(WHITE_FIN)$(CFLAGS)\n$(NO_COLOR)"
	@printf "%b" "$(OBJ_COLOR)Credits:	$(WHITE_FIN)tmatis (42make)\n"
	@echo


-include $(DEPS) $(DEPS_MAIN)
$(NAME):	${OBJS} ${OBJ_MAIN}
			@$(call display_progress_bar)
			@$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -I$(INCLUDE_PATH) -o $@ ${OBJS} ${OBJ_MAIN})

setup:
	@$(call save_files_changed)

objs/%.o: 	$(SRCS_PATH)/%$(FILE_EXTENSION)
			@mkdir -p $(dir $@)
			@$(call display_progress_bar)
			@$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I$(INCLUDE_PATH))

clean:		header
			@rm -rf objs objs_tests
			@printf "%-53b%b" "$(COM_COLOR)clean:" "$(GREEN)[✓]$(NO_COLOR)\n"

fclean:		header clean
			@rm -rf $(NAME)
			@printf "%-53b%b" "$(COM_COLOR)fclean:" "$(GREEN)[✓]$(NO_COLOR)\n"

re:			fclean all

.PHONY:		all clean fclean re header
