# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 13:06:26 by pdolinar          #+#    #+#              #
#    Updated: 2022/10/26 17:50:06 by fsemke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
RM			:=	rm -rf

# dependencies
INC			:=	include
LIBFT_DIR 	:=	./libft
INC_L		:=	$(LIBFT_DIR)/$(INC)
LIBFT 		:=	$(LIBFT_DIR)/libft.a
HEADER		:=	$(INC)/minishell.h
HEADER_L	:=	$(LIBFT_DIR)/$(INC)/libft.h

# readline dependencies
RDLINE_DEP		= $(RDLINE_$(shell uname -s))
RDLINE_Linux	:=	-L /usr/local/opt/readline/lib
RDLINE_Darwin	:= $(HEADER_MAC) -L /goinfre/${USER}/.brew/opt/readline/lib/
HEADER_MAC		:=	-I $(HOME)/goinfre/.brew/opt/readline/include/
RDLINE_FLAG		:=	-lreadline

# miscellaneous
CLEAR := \033[0m
PR := \033[1;35m
GR := \033[1;32m

# source dir
SRCS_DIR :=	srcs
MAIN_DIR := /main/
MISC_DIR := /misc/
EXEC_DIR := /exec/
PARS_DIR := /pars/
REDIR_DIR := /redir/
BUILTINS_DIR := /builtins/

# source files
MAIN := main.c
MISC := init.c utils.c utils_2.c cleanup.c signals.c errors.c
EXEC := cmd.c exec.c piping.c processes.c
PARS := parsing.c parsing_utils.c parsing_identify.c parsing_errorcheck.c path.c
REDIR := redirection.c heredoc.c
BUILTINS := builtins.c builtins2.c builtins_export.c print_export.c ext_env.c history.c

SRCS	=	$(addprefix $(SRCS_DIR), $(addprefix $(MAIN_DIR), $(MAIN))) \
			$(addprefix $(SRCS_DIR), $(addprefix $(MISC_DIR), $(MISC))) \
			$(addprefix $(SRCS_DIR), $(addprefix $(EXEC_DIR), $(EXEC))) \
			$(addprefix $(SRCS_DIR), $(addprefix $(REDIR_DIR), $(REDIR))) \
			$(addprefix $(SRCS_DIR), $(addprefix $(BUILTINS_DIR), $(BUILTINS))) \
			$(addprefix $(SRCS_DIR), $(addprefix $(PARS_DIR), $(PARS)))

OBJS	=	$(patsubst %.c,%.o,$(SRCS))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(RDLINE_DEP) $(RDLINE_FLAG)
	@echo "$(GR)> Compiled & linked!									   \n \
      _______ _____ __   _ _____ _______ _     _ _______               \n \
      |  |  |   |   | \  |   |   |______ |_____| |______ |      |      \n \
      |  |  | __|__ |  \_| __|__ ______| |     | |______ |_____ |_____ \n \
                                                             		$(REV)"

%.o:%.c $(HEADER) $(HEADER_L)
	@$(CC) $(CFLAGS) -I $(INC) -I $(INC_L) $(HEADER_MAC) -c $< -o $@

$(LIBFT):
	@$(MAKE) all -s -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) fclean -s -C $(LIBFT_DIR)
	@echo "$(PR)All object files deleted$(CLEAR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(PR)$(NAME) deleted$(CLEAR)"

norm:
	@norminette $(SRC_DIR)

re:	fclean all

.PHONY: all clean fclean re norm
