BONUS_SRCS 		= philo_bonus.c philo_actions.c philo_utils.c ft_atoi.c
BONUS_NAME 		= philo_bonus
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_SRCS)
	$(CC) $(CFLAGS) $(BONUS_SRCS) -o $(BONUS_NAME)

fclean:
	rm -f $(BONUS_NAME)

re : fclean all

.PHONY: re all fclean