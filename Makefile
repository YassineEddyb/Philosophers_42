SRCS	= philo.c philo_actions.c philo_utils.c ft_atoi.c
NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) -o $(NAME) -fsanitize=address

fclean:
	rm -f $(NAME)

re : fclean all

.PHONY: re all fclean