/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:40:31 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/23 11:31:26 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *philo, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_create(&(philo[i].thread_id), NULL, &sumulate, &(philo[i]));
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < num_of_philos)
	{
		pthread_create(&(philo[i].thread_id), NULL, &sumulate, &(philo[i]));
		i += 2;
	}
}

void	get_philos_data(t_philo *philo, char **argv, int argc, int philos)
{
	int				i;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg;

	dead = 0;
	msg = malloc(1 * sizeof(pthread_mutex_t));
	pthread_mutex_init(msg, NULL);
	forks = malloc(philos * sizeof(pthread_mutex_t));
	init_forks(forks, philos);
	i = 0;
	while (i < philos)
	{
		init_data(&(philo[i]), argv, argc);
		philo[i].meals_counter = 0;
		philo[i].dead = &dead;
		philo[i].forks = forks;
		philo[i].last_meal = get_time();
		philo[i].philo_id = i + 1;
		philo[i].msg = msg;
		philo[i].start_time = get_time();
		i++;
	}
	create_threads(philo, philos);
}

void	*sumulate(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->forks[philo->philo_id - 1]));
		take_fork(philo);
		pthread_mutex_lock(&(philo->forks[philo->philo_id % philo->philos]));
		take_fork(philo);
		if (philo->time_to_die < philo->time_to_eat)
			dead(philo, philo->time_to_die, "eating");
		else
			eating(philo);
		pthread_mutex_unlock(&(philo->forks[philo->philo_id % philo->philos]));
		pthread_mutex_unlock(&(philo->forks[philo->philo_id - 1]));
		if (is_about_to_die(philo, philo->time_to_sleep))
			dead(philo, is_about_to_die(philo, \
			philo->time_to_sleep), "sleeping");
		else
			sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*count_meals(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo[i].philos)
		{
			if (*(philo[i].dead) == 1)
			{
				distroy_mutexes(philo->forks, philo->msg, philo->philos);
				return (NULL);
			}
			if (philo[i].meals_counter < philo[i].number_of_meals)
				break ;
			if (i == philo[i].philos - 1)
			{
				distroy_mutexes(philo->forks, philo->msg, philo->philos);
				return (NULL);
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	int			num_of_philos;
	t_philo		*philo;
	pthread_t	id;

	num_of_philos = ft_atoi(argv[1]);
	philo = malloc(num_of_philos * sizeof(t_philo));
	get_philos_data(philo, argv, argc, num_of_philos);
	if (argc == 6)
	{
		pthread_create(&id, NULL, &count_meals, philo);
		if (pthread_join(id, NULL) == 0)
			return (0);
	}
	while (1)
	{
		if (*(philo->dead) == 1)
		{
			distroy_mutexes(philo->forks, philo->msg, num_of_philos);
			return (0);
		}
	}
	system("leaks philo");
}
