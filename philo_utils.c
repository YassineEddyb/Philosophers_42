/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:44:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/02/16 11:45:32 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int get_time()
{
	struct timeval start;
	gettimeofday(&start, NULL);
    return (start.tv_sec * 1000000 + start.tv_usec);
}

long int is_about_to_die(t_philo *philo)
{
	if (philo->time_to_die - (get_time() - philo->start_time - philo->last_meal) < philo->time_to_sleep)
		return(philo->time_to_die - (get_time() - philo->start_time - philo->last_meal));
	return (0);
}