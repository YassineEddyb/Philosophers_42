/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:44:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/21 19:35:54 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000000 + start.tv_usec);
}

long int	is_about_to_die(t_philo *philo, long time_to)
{
	if (philo->time_to_die - (get_time() - philo->last_meal) < time_to)
		return (philo->time_to_die - (get_time() - philo->last_meal));
	return (0);
}

void	ft_usleep(long delay)
{
	long int	start;

	start = get_time();
	while (get_time() - start < delay)
		usleep(1);
}

void	init_data(t_philo *philo, char **argv, int argc)
{
	philo->philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		philo->number_of_meals = ft_atoi(argv[5]);
}

// void	init_forks(pthread_mutex_t *forks, int num_of_philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < num_of_philos)
// 	{
// 		sem_open("fork", O_CREAT, 0664, 1);
// 		i++;
// 	}
// }
