/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:40:31 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/24 10:09:07 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_procceses(t_philo *philo, int num_of_philos)
{
	int	i;
	int	pid;

	i = 0;
	while (i < num_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			sumulate(&(philo[i]));
			exit(0);
		}
		else
			philo[i].pid = pid;
		i++;
	}
}

void	get_philos_data(t_philo *philo, char **argv, int argc, int nphilos)
{
	int		i;
	int		dead;
	sem_t	*forks;
	sem_t	*msg;

	forks = NULL;
	msg = NULL;
	init_semaphores(forks, msg, nphilos);
	dead = 0;
	i = 0;
	while (i < nphilos)
	{
		init_data(&(philo[i]), argv, argc);
		philo[i].meals_counter = 0;
		philo[i].dead = &dead;
		philo[i].forks = forks;
		philo[i].last_meal = get_time();
		philo[i].philo_id = i + 1;
		philo[i].msg = msg;
		philo[i].start_time = get_time();
		philo[i].argc = argc;
		i++;
	}
	create_procceses(philo, nphilos);
}

void	sumulate(t_philo *philo)
{
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
	int		status;
	int		num_of_philos;
	t_philo	*philo;
	int		i;

	num_of_philos = ft_atoi(argv[1]);
	philo = malloc(num_of_philos * sizeof(t_philo));
	get_philos_data(philo, argv, argc, num_of_philos);
	i = 0;
	while (i < num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0)
		{
			kill_all_proccessors(philo);
			exit(0);
		}
		i++;
	}
	kill_all_proccessors(philo);
}
