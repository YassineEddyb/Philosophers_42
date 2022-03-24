/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:05:30 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/24 10:08:39 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_philo *philo, char **argv, int argc)
{
	philo->philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->number_of_meals = ft_atoi(argv[5]);
}

void	init_semaphores(sem_t *forks, sem_t *msg, int nphilos)
{
	sem_unlink("msg");
	sem_unlink("semaphore");
	msg = sem_open("msg", O_CREAT | O_EXCL, 0644, 1);
	if (msg == SEM_FAILED)
		exit(1);
	forks = sem_open("semaphore", O_CREAT | O_EXCL, 0644, nphilos);
	if (forks == SEM_FAILED)
		exit(1);
}
