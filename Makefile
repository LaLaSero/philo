NAME = philo
SRCS = srcs/main.c srcs/check_args.c srcs/utils_func.c srcs/life_of_philo.c srcs/process_game.c 
SRCS += srcs/init_game.c srcs/print_status.c srcs/judge_gameover.c
INCLUDE = includes
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c $(INCLUDE)
	$(CC) -c $(CFLAGS) -o $@ $< -I $(INCLUDE)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
