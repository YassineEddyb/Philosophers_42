/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:40:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/02/16 11:41:26 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(t_philo *philo)
{
    printf("\033[0;32m%ld %d is eating\n",(get_time() - philo->start_time) / 1000, philo->philo_id);
	philo->last_meal = get_time() - philo->start_time;
    usleep(philo->time_to_eat);
}

void sleeping(t_philo *philo)
{
    printf("\033[0;33m%ld %d is sleeping\n",(get_time() - philo->start_time) / 1000, philo->philo_id);
    usleep(philo->time_to_sleep);
}

void thinking(t_philo *philo)
{
    printf("\033[0;34m%ld %d is thinking\n",(get_time() - philo->start_time) / 1000, philo->philo_id);
}

void take_fork(t_philo *philo)
{
    printf("\033[0;35m%ld %d has take a fork\n",(get_time() - philo->start_time) / 1000, philo->philo_id);
}

void dead (t_philo *philo, int s)
{
	int retv;

	retv = 100;
	printf("\033[0;33m%ld %d is sleeping\n",(get_time() - philo->start_time) / 1000, philo->philo_id);
	usleep(s);
	printf("\033[0;31m%ld %d is dead\n", (get_time() - philo->start_time) / 1000, philo->philo_id);
	pthread_exit(&retv);
}