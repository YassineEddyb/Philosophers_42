/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:44:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/25 15:50:53 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000000 + start.tv_usec) / 1000);
}

void	ft_usleep(long delay)
{
	long int	start;

	start = get_time();
	while (get_time() - start < delay)
		usleep(100);
}

void	destroy_mutexes(pthread_mutex_t *forks, \
		pthread_mutex_t *msg, int nphilos)
{
	int	i;

	i = 0;
	while (i < nphilos)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
	pthread_mutex_destroy(msg);
}

int	check_death(t_philo *philo, int nphilos)
{
	int	i;

	i = 0;
	while (i < nphilos)
	{
		if (get_time() - philo[i].last_meal > philo[i].time_to_die)
		{
			dead(&(philo[i]));
			destroy_mutexes(philo->forks, philo->msg, philo->nphilos);
			return (0);
		}
	}
	return (1);
}
