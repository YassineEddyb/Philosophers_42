/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:35:02 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/25 15:21:03 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->msg);
	printf("%ld %d is eating\n", \
		(get_time() - philo->start_time), philo->philo_id);
	pthread_mutex_unlock(philo->msg);
	philo->last_meal = get_time();
	ft_usleep(philo->time_to_eat);
	(philo->meals_counter)++;
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->msg);
	printf("%ld %d is sleeping\n", \
		(get_time() - philo->start_time), philo->philo_id);
	pthread_mutex_unlock(philo->msg);
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->msg);
	printf("%ld %d is thinking\n", \
		(get_time() - philo->start_time), philo->philo_id);
	pthread_mutex_unlock(philo->msg);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->msg);
	printf("%ld %d has take a fork\n", \
		(get_time() - philo->start_time), philo->philo_id);
	pthread_mutex_unlock(philo->msg);
}

void	dead(t_philo *philo)
{
	pthread_mutex_lock(philo->msg);
	printf("\033[0;31m%ld %d died\n", \
		(get_time() - philo->start_time), philo->philo_id);
}
