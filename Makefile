NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g
READLINE = -lreadline
LIBFT = libft.a
LIBFT_LOC = libft/
SRCS = main.c lexer.c rules.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LOC)$(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_LOC) -lft $(READLINE)

$(LIBFT_LOC)$(LIBFT):
	$(MAKE) -C $(LIBFT_LOC)

clean:
	$(MAKE) -C $(LIBFT_LOC) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_LOC) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
