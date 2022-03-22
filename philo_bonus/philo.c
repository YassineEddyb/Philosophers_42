/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:40:31 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/22 14:47:49 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_procceses(t_philo *philo, int num_of_philos)
{
	int	i;
	int pid;

	i = 0;
	while (i < num_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			philo[i].pid = getpid();
			sumulate(philo, i);
			// usleep(10);
			exit(0);
		}
		i++;
	}
}

void	get_philos_data(t_philo *philo, char **argv, int argc, int philos)
{
	int				i;
	int				dead;
	sem_t	*forks;
	sem_t	*msg;

	dead = 0;
	sem_unlink("msg");
	sem_unlink("semaphore");
	msg = sem_open("msg", O_CREAT | O_EXCL, 0644, 1);
	if(msg == SEM_FAILED)
		exit(1);
	forks = sem_open("semaphore", O_CREAT | O_EXCL, 0644, philos);
	if(forks == SEM_FAILED)
		exit(1);
	i = 0;
	while (i < philos)
	{
		init_data(&(philo[i]), argv, argc);
		philo[i].meals_counter = 0;
		philo[i].dead = &dead;
		philo[i].forks = forks;
		philo[i].last_meal = get_time();
		philo[i].philo_id = i + 1;
		philo[i].msg = msg;
		philo[i].start_time = get_time();
		i++;
	}
	create_procceses(philo, philos);
}

void	*sumulate(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->forks);
		take_fork(philo);
		sem_wait(philo->forks);
		take_fork(philo);
		if (philo->time_to_die < philo->time_to_eat)
			dead(philo, philo->time_to_die, "eating");
		else
			eating(philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		if (is_about_to_die(philo, philo->time_to_sleep))
			dead(philo, is_about_to_die(philo, \
			philo->time_to_sleep), "sleeping");
		else
			sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void kill_all_proccessors(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->philos)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}

void	*count_meals(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo[i].philos)
		{
			if (*(philo[i].dead) == 1)
			{
				printf("Ok\n");
				kill_all_proccessors(philo);
				exit(0);
			}
			printf("%d\n", philo[i].meals_counter);
			if (philo[i].meals_counter < philo[i].number_of_meals)
				break ;
			if (i == philo[i].philos - 1)
			{
				kill_all_proccessors(philo);
				exit(0);
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	// int		 	i;
	int			num_of_philos;
	t_philo		*philo;
	pthread_t	id;

	num_of_philos = ft_atoi(argv[1]);
	philo = malloc(num_of_philos * sizeof(t_philo));
	get_philos_data(philo, argv, argc, num_of_philos);
	if (argc == 6)
	{
		pthread_create(&id, NULL, &count_meals, philo);
		if (pthread_join(id, NULL) == 0)
			exit(0);
	}

	waitpid(-1, NULL, 0);
}
