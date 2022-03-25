/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:34:40 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/25 18:35:18 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_philo {
	pid_t		pid;
	int			philo_id;
	int			philos;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	int			number_of_meals;
	int			meals_counter;
	sem_t		*forks;
	sem_t		*msg;
	long int	start_time;
	int long	last_meal;
	int			argc;
	int			*dead;
}	t_philo;

void		sumulate(t_philo *philo);
int			ft_atoi(const char *str);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		take_fork(t_philo *philo);
long int	get_time(void);
void		ft_usleep(long delay);
void		fill_data(t_philo *philo, char **argv, \
				pthread_mutex_t *forks, int i);
void		init_data(t_philo *philo, char **argv, int argc);
void		init_semaphore(t_philo *philo, int i);
void		kill_all_proccessors(t_philo *philo);

#endif