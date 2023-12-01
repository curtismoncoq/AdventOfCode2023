# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 21:44:32 by cumoncoq          #+#    #+#              #
#    Updated: 2023/12/01 21:59:49 by cumoncoq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = count.c

LIBFTDIR = ../libft

LIBFT = $(LIBFTDIR)/libft.a

OBJS = $(addprefix $(OBJDIR),$(SRCS:.c=.o))

OBJDIR = objs/

NAME = counting

file = file.txt

CC = cc

CFLAGS = -Wall -Wextra -Werror

$(OBJDIR)%.o : %.c
	@mkdir -p $(OBJDIR)
	@${CC} ${CFLAGS} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft

clean:
	@rm -f $(OBJS)
	@rmdir $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

x: $(NAME)
	@./$(NAME) $(file)
	@make fclean

.PHONY: all clean fclean re x
