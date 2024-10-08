# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 21:33:36 by iniska            #+#    #+#              #
#    Updated: 2024/10/09 10:08:45 by iniska           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Wextra -Werror

SRCFILES 	= 	main.c parsing.c set_the_table.c mutex_handln.c \
				is_number.c start_thinking.c clean_n_errors.c cleanup.c \
				eating.c situation_checker.c routine.c lonely_philo.c \
				ft_latoi.c

SRCDIR		=	src
OBJDIR		=	objs

HEADER		=	philo.h

SRCS		=	$(addprefix $(SRCDIR)/, $(SRCFILES))

OBJS		= 	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

ANSI_CYAN 	:= 	\033[0;36m
ANSI_BLUE 	:= 	\033[0;34m
ANSI_RED 	:= 	\033[31m
ANSI_RESET 	:= 	\033[0m

all: 			$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER)
				@mkdir -p $(OBJDIR)
				@cc $(FLAGS) -o $@ -c $<

$(NAME):		$(OBJS)
				@cc $(HEADERS) $(OBJS) -lreadline -o $(NAME)
				@echo "$(ANSI_CYAN)Compilation Complete: $(NAME) $(ANSI_RESET)"

clean:
				@rm -rf $(OBJDIR)
				
				@echo "$(ANSI_RED)Objects and LIB_FT Cleaned$(ANSI_RESET)"

fclean:			clean
				@rm -rf $(NAME)
				@echo "$(ANSI_RED)Executable $(NAME) removed$(ANSI_RESET)"

re:				fclean all