SRCS			= philo_bonus.c philo_actions_bonus.c philo_utils_bonus.c philo_inits_bonus.c ft_atoi.c
NAME			= philo_bonus
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: re all fclean