/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:44:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/04 11:19:34 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int get_time()
{
	struct timeval start;
	gettimeofday(&start, NULL);
    return (start.tv_sec * 1000000 + start.tv_usec);
}

long int is_about_to_die(t_philo *philo, long time_to)
{
	if (philo->time_to_die - (get_time() - philo->start_time - philo->last_meal) < time_to)
		return(philo->time_to_die - (get_time() - philo->start_time - philo->last_meal));
	return (0);
}

void ft_usleep(long delay)
{
	long int start;

	start = get_time();
	while(get_time() - start < delay)
		usleep(10);
}
