/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:40:31 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/05 11:19:12 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_forks(pthread_mutex_t *forks, int num_of_philos)
{
    int i;

    i = 0;
    while(i < num_of_philos)
    {
        pthread_mutex_init(&(forks[i]), NULL);
        i++;
    }
}

void create_threads(t_philo *philo, int num_of_philos)
{
    int i;

    i = 0;
    while(i < num_of_philos)
    {
        pthread_create(&(philo[i].thread_id), NULL, &sumulate, &(philo[i]));
        i += 2;
    }
    usleep(100);
    i = 1;
    while(i < num_of_philos)
    {
        pthread_create(&(philo[i].thread_id), NULL, &sumulate, &(philo[i]));
        i += 2;
    }
}

void get_philos_data(t_philo *philo, char **argv, int argc, int num_of_philos)
{
    int i;
    int dead = 0;
    pthread_mutex_t *forks;
    pthread_mutex_t msg;

    pthread_mutex_init(&msg, NULL);
    forks = malloc(num_of_philos * sizeof(pthread_mutex_t));
    init_forks(forks, num_of_philos);
    i = 0;
    while(i < num_of_philos)
    {
        philo[i].num_of_philos = ft_atoi(argv[1]);
        philo[i].time_to_die = ft_atoi(argv[2]) * 1000;
        philo[i].time_to_eat = ft_atoi(argv[3]) * 1000;
        philo[i].time_to_sleep = ft_atoi(argv[4]) * 1000;
        if (argc == 6)
            philo[i].number_of_meals = ft_atoi(argv[5]);
        philo[i].meals_counter = 0;
        philo[i].dead = &dead;
        philo[i].time_stamp = 0;
        philo[i].forks = forks;
        philo[i].last_meal = get_time();
        philo[i].philo_id = i + 1;
        philo[i].msg = &msg;
        philo[i].start_time = get_time();
        i++;
    }
    create_threads(philo, num_of_philos);
}

void *sumulate(void *arg)
{
	t_philo *philo;
    int next_philo_id;

	philo = (t_philo *)arg;
    if (philo->philo_id == philo->num_of_philos)
        next_philo_id = 1;
    else
        next_philo_id = philo->philo_id + 1;
    while(1)
    {
        pthread_mutex_lock(&(philo->forks[philo->philo_id - 1]));
        take_fork(philo);
        pthread_mutex_lock(&(philo->forks[next_philo_id - 1]));
        take_fork(philo);
        if (philo->time_to_die < philo->time_to_eat)
        {
            pthread_mutex_lock(philo->msg);
            dead(philo, philo->time_to_die, "eating");
            return (NULL);
        } else
            eating(philo);
        pthread_mutex_unlock(&(philo->forks[next_philo_id - 1]));
        pthread_mutex_unlock(&(philo->forks[philo->philo_id - 1]));
        if (is_about_to_die(philo, philo->time_to_sleep))
        {
            pthread_mutex_lock(philo->msg);
            dead(philo, is_about_to_die(philo, philo->time_to_sleep), "sleeping");
            return (NULL);
        } else
            sleeping(philo);
        thinking(philo);
    }
    return NULL;
}

void *count_meals(void *arg)
{
    int i;
	t_philo *philo;

	philo = (t_philo *)arg;
    while(1)
    {
        i = 0;
        while (i < philo[i].num_of_philos)
        {
            if (philo[i].meals_counter < philo[i].number_of_meals)
                break ;
            if (i == philo[i].num_of_philos - 1)
                return (NULL);
            i++;
        }
    }
}

void *is_dead(void *arg)
{
    int i;
	t_philo *philo;

	philo = (t_philo *)arg;
    while(1)
    {
        i = 0;
        while (i < philo[i].num_of_philos)
        {
            if (*(philo[i].dead) == 1)
            {
                printf("\033[0;31m%ld %d is dead\n",(get_time() - philo[i].start_time) / 1000, philo[i].philo_id);
                return (NULL);
            }
            i++;
        }
    }
}

int main(int argc, char **argv)
{
    int i;
    int num_of_philos;
    t_philo *philo;
    //size_t start_time;
    pthread_t id1;
    pthread_t id2;

    num_of_philos = ft_atoi(argv[1]);
    philo = malloc(num_of_philos * sizeof(t_philo));

    get_philos_data(philo, argv, argc, num_of_philos);
    i = 0;
    while(i < num_of_philos)
    {
        pthread_create(&id2, NULL, &is_dead, philo);
        if (!pthread_join(id2, NULL))
            return (0);
        if (argc == 6)
        {
            pthread_create(&id1, NULL, &count_meals, philo);
            if (!pthread_join(id1, NULL))
                return (0);
        }
        if (!pthread_join(philo[i].thread_id, NULL))
            return (0);
        i++;
    }
}