SRCS			= philo.c philo_actions.c philo_utils.c ft_atoi.c
SRCS_PRF 		= $(addprefix philo/, $(SRCS))
BONUS_SRCS 		= philo_bonus.c philo_actions.c philo_utils.c ft_atoi.c
BONUS_SRCS_PRF	= $(addprefix philo_bonus/, $(BONUS_SRCS))
NAME			= philo
BONUS_NAME 		= philo_bonus
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(SRCS_PRF)
	$(CC) $(CFLAGS) $(SRCS_PRF) -lpthread -o $(NAME)

fclean:
	rm -f ./philo/$(NAME) ./philo_bonus/$(BONUS_NAME)

re : fclean all

bonus: $(BONUS_SRCS_PRF)
	$(CC) $(CFLAGS) $(BONUS_SRCS_PRF) -o $(BONUS_NAME)

.PHONY: re all fclean