/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:35:02 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/24 09:50:28 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->msg);
	printf("\033[0;32m%ld %d is eating\n", \
		(get_time() - philo->start_time), philo->philo_id);
	sem_post(philo->msg);
	philo->last_meal = get_time();
	ft_usleep(philo->time_to_eat);
	if (philo->argc == 6)
	{
		philo->meals_counter += 1;
		if (philo->meals_counter == philo->number_of_meals)
		{
			sem_post(philo->forks);
			sem_post(philo->forks);
			exit(2);
		}
	}
}

void	sleeping(t_philo *philo)
{
	sem_wait(philo->msg);
	printf("\033[0;33m%ld %d is sleeping\n", \
		(get_time() - philo->start_time), philo->philo_id);
	sem_post(philo->msg);
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	sem_wait(philo->msg);
	printf("\033[0;34m%ld %d is thinking\n", \
		(get_time() - philo->start_time), philo->philo_id);
	sem_post(philo->msg);
}

void	take_fork(t_philo *philo)
{
	sem_wait(philo->msg);
	printf("\033[0;35m%ld %d has take a fork\n", \
		(get_time() - philo->start_time), philo->philo_id);
	sem_post(philo->msg);
}

void	dead(t_philo *philo, int s, char *str)
{
	sem_wait(philo->msg);
	printf("\033[0;33m%ld %d is %s\n", (get_time() - \
		philo->start_time), philo->philo_id, str);
	sem_post(philo->msg);
	ft_usleep(s);
	sem_wait(philo->msg);
	printf("\033[0;31m%ld %d died\n", \
		(get_time() - philo->start_time), philo->philo_id);
	*(philo->dead) = 1;
	exit(0);
}
