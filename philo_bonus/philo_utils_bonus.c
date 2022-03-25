/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:44:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/25 18:34:14 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	kill_all_proccessors(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philos)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}
