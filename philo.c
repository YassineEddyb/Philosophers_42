/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:40:31 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/02/16 11:44:55 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *sumulate(void *arg)
{
	t_philo *philo;
    int prev_philo_id;

	philo = (t_philo *)arg;
    if (philo->philo_id == philo->num_of_philos)
        prev_philo_id = 1;
    else
        prev_philo_id = philo->philo_id + 1;

    while(1)
    {
        pthread_mutex_lock(&(philo->forks[philo->philo_id]));
        pthread_mutex_lock(&(philo->forks[prev_philo_id]));

        take_fork(philo);
        take_fork(philo);
        eating(philo);

        pthread_mutex_unlock(&(philo->forks[prev_philo_id]));
        pthread_mutex_unlock(&(philo->forks[philo->philo_id]));
		if (!is_about_to_die(philo))
        	sleeping(philo);
		else
			dead(philo ,is_about_to_die(philo));
        thinking(philo);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    int i;
    int num_of_philos;
    t_philo *philo;
    pthread_mutex_t *forks;
    size_t start_time;

    num_of_philos = ft_atoi(argv[1]);
    philo = malloc(num_of_philos * sizeof(t_philo));
    forks = malloc(num_of_philos * sizeof(pthread_mutex_t));

    i = 0;
    while(i < num_of_philos)
    {
        pthread_mutex_init(&(forks[i]), NULL);
        i++;
    }

    i = 0;
    while (i < num_of_philos)
    {
        if (i % 2 == 0)
        {
            philo[i].num_of_philos = num_of_philos;
            philo[i].time_to_die = ft_atoi(argv[2]) * 1000;
            philo[i].time_to_eat = ft_atoi(argv[3]) * 1000;
            philo[i].time_to_sleep = ft_atoi(argv[4]) * 1000;
            philo[i].time_stamp = 0;
            philo[i].forks = forks;
            philo[i].philo_id = i + 1;
			philo[i].start_time = get_time();
            pthread_create(&(philo[i].thread_id), NULL, &sumulate, &philo[i]);
        }
        i++;
    }
    usleep(100);

    i = 0;
    while (i < num_of_philos)
    {
        if (i % 2 != 0)
        {
            philo[i].num_of_philos = num_of_philos;
            philo[i].time_to_die = ft_atoi(argv[2]) * 1000;
            philo[i].time_to_eat = ft_atoi(argv[3]) * 1000;
            philo[i].time_to_sleep = ft_atoi(argv[4]) * 1000;
            philo[i].time_stamp = 0;
            philo[i].forks = forks;
            philo[i].philo_id = i + 1;
			philo[i].start_time = get_time();
            pthread_create(&(philo[i].thread_id), NULL, &sumulate, &philo[i]);
        }
        i++;
    }

    i = 0;
    while(i < num_of_philos)
    {
        pthread_join(philo[i].thread_id, NULL);
        i++;
    }
}