/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:07:57 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/23 11:17:29 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_philo *philo, char **argv, int argc)
{
	philo->philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		philo->number_of_meals = ft_atoi(argv[5]);
}

void	init_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&(forks[i]), NULL);
		i++;
	}
}
