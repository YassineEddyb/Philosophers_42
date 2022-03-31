/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:40:31 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/31 09:41:56 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *philo, int nphilos)
{
	int	i;

	i = 0;
	while (i < nphilos)
	{
		pthread_create(&(philo[i].thread_id), NULL, &sumulate, &(philo[i]));
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < nphilos)
	{
		pthread_create(&(philo[i].thread_id), NULL, &sumulate, &(philo[i]));
		i += 2;
	}
}

void	get_philos_data(t_philo *philo, char **argv, int argc, int nphilos)
{
	int				i;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg;

	msg = malloc(1 * sizeof(pthread_mutex_t));
	pthread_mutex_init(msg, NULL);
	forks = malloc(nphilos * sizeof(pthread_mutex_t));
	init_forks(forks, nphilos);
	i = 0;
	while (i < nphilos)
	{
		init_data(&(philo[i]), argv, argc);
		philo[i].meals_counter = 0;
		philo[i].forks = forks;
		philo[i].last_meal = get_time();
		philo[i].philo_id = i + 1;
		philo[i].msg = msg;
		philo[i].start_time = get_time();
		i++;
	}
	create_threads(philo, nphilos);
}

void	*sumulate(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->forks[philo->philo_id - 1]));
		take_fork(philo);
		pthread_mutex_lock(&(philo->forks[philo->philo_id % philo->nphilos]));
		take_fork(philo);
		eating(philo);
		pthread_mutex_unlock(&(philo->forks[philo->philo_id % philo->nphilos]));
		pthread_mutex_unlock(&(philo->forks[philo->philo_id - 1]));
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
		while (i < philo[i].nphilos)
		{
			if (get_time() - philo[i].last_meal > philo[i].time_to_die)
			{
				dead(&(philo[i]));
				destroy_mutexes(philo->forks, philo->msg, philo->nphilos);
				return (0);
			}
			if (philo[i].meals_counter < philo[i].number_of_meals)
				break ;
			if (i == philo[i].nphilos - 1)
			{
				destroy_mutexes(philo->forks, philo->msg, philo->nphilos);
				return (NULL);
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	int			nphilos;
	t_philo		*philo;
	pthread_t	id;

	if (argc < 5 || argc > 6 || is_numbers(argv))
	{
		printf("Usage: number_of_philosophers[number] time_to_die[number] \n\
		time_to_eat[number] time_to_sleep[number]\n");
		exit(1);
	}
	nphilos = ft_atoi(argv[1]);
	philo = malloc(nphilos * sizeof(t_philo));
	get_philos_data(philo, argv, argc, nphilos);
	if (argc == 6)
	{
		pthread_create(&id, NULL, &count_meals, philo);
		if (pthread_join(id, NULL) == 0)
			return (0);
	}
	while (1)
	{
		if (!check_death(philo, nphilos))
			return (0);
	}
}
