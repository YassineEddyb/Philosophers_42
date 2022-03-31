/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:34:40 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/30 15:00:56 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo {
	pthread_t		thread_id;
	int				philo_id;
	int				nphilos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				number_of_meals;
	int				meals_counter;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg;
	long int		start_time;
	int long		last_meal;
}	t_philo;

void		*sumulate(void *arg);
int			ft_atoi(const char *str);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		take_fork(t_philo *philo);
void		dead(t_philo *philo);
long int	get_time(void);
void		ft_usleep(long delay);
int			check_death(t_philo *philo, int nphilos);
void		fill_data(t_philo *philo, char **argv, \
				pthread_mutex_t *forks, int i);
void		init_data(t_philo *philo, char **argv, int argc);
void		init_forks(pthread_mutex_t *forks, int num_of_philos);
int			is_numbers(char **argv);
void		destroy_mutexes(pthread_mutex_t *forks, \
				pthread_mutex_t *msg, int nphilos);

#endif