/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:30:01 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/04 11:40:25 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void init_forks(sem_t *forks, int num_of_philos)
{
    int i;

    i = 0;
    while(i < num_of_philos)
    {
        forks[i] = (sem_t)sem_open("/mysem", O_CREAT,0664, 0);
        i++;
    }
}

void create_proccessors(t_philo *philo, int num_of_philos)
{
    int i;

    i = 0;
    while(i < num_of_philos)
    {
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			sumulate(&(philo[i]));
			exit(1);
		}
		i += 2;
    }
    usleep(100);
    i = 1;
    while(i < num_of_philos)
    {
        philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			sumulate(&(philo[i]));
			exit(1);
		}
		i += 2;
    }
}

void get_philos_data(t_philo *philo, char **argv, int argc, int num_of_philos)
{
    int i;
    sem_t *forks;
    pthread_mutex_t msg;

    pthread_mutex_init(&msg, NULL);
    forks = malloc(num_of_philos * sizeof(sem_t));
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
        philo[i].dead = 0;
        philo[i].time_stamp = 0;
        philo[i].forks = forks;
        philo[i].last_meal = get_time();
        philo[i].philo_id = i + 1;
        philo[i].msg = &msg;
        philo[i].start_time = get_time();
        i++;
    }
    create_proccessors(philo, num_of_philos);
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
        sem_wait(&(philo->forks[philo->philo_id - 1]));
        take_fork(philo);
        sem_wait(&(philo->forks[next_philo_id - 1]));
        take_fork(philo);
        if (philo->time_to_die < philo->time_to_eat)
        {
            dead(philo, philo->time_to_die, "eating");
            return NULL;
        } else
            eating(philo);
       sem_post(&(philo->forks[next_philo_id - 1]));
       sem_post(&(philo->forks[philo->philo_id - 1]));
        if (is_about_to_die(philo, philo->time_to_sleep))
        {
            dead(philo, is_about_to_die(philo, philo->time_to_sleep), "sleeping");
            return NULL;
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
            if (philo[i].dead == 1)
                return (NULL);
            if (philo[i].meals_counter < philo[i].number_of_meals)
                break ;
            if (i == philo[i].num_of_philos - 1)
                return (NULL);
            i++;
        }
        usleep(100);
    }
}

int main(int argc, char **argv)
{
    int i;
    int num_of_philos;
    t_philo *philo;

    num_of_philos = ft_atoi(argv[1]);
    philo = malloc(num_of_philos * sizeof(t_philo));

    get_philos_data(philo, argv, argc, num_of_philos);
    i = 0;
	while(i < num_of_philos)
	{
		waitpid(philo[i].pid, NULL, 0);
		i++;
	}
}