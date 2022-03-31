/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:40:31 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/03/30 15:13:58 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_procceses(t_philo *philo, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			sumulate(&(philo[i]));
			exit(0);
		}
		i++;
	}
}

void	get_philos_data(t_philo *philo, char **argv, int argc, int nphilos)
{
	int		i;
	sem_t	*forks;
	sem_t	*msg;

	sem_unlink("msg");
	sem_unlink("semaphore");
	msg = sem_open("msg", O_CREAT | O_EXCL, 0644, 1);
	if (msg == SEM_FAILED)
		exit(1);
	forks = sem_open("semaphore", O_CREAT | O_EXCL, 0644, nphilos);
	if (forks == SEM_FAILED)
		exit(1);
	i = 0;
	while (i < nphilos)
	{
		init_data(&(philo[i]), argv, argc);
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

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time() - philo->last_meal > philo->time_to_die)
		{
			sem_wait(philo->msg);
			printf("\033[0;31m%ld %d died\n", \
				(get_time() - philo->start_time), philo->philo_id);
			exit(0);
		}
		usleep(100);
	}
}

void	sumulate(t_philo *philo)
{
	pthread_t	id;

	pthread_create(&id, NULL, &check_death, philo);
	while (1)
	{
		sem_wait(philo->forks);
		sem_wait(philo->msg);
		printf("%ld %d has take a fork\n", \
			(get_time() - philo->start_time), philo->philo_id);
		sem_post(philo->msg);
		sem_wait(philo->forks);
		sem_wait(philo->msg);
		printf("%ld %d has take a fork\n", \
			(get_time() - philo->start_time), philo->philo_id);
		sem_post(philo->msg);
		eating(philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		sleeping(philo);
		thinking(philo);
	}
}

int	main(int argc, char **argv)
{
	int		status;
	int		num_of_philos;
	t_philo	*philo;
	int		i;

	if (argc < 5 || argc > 6 || is_numbers(argv))
	{
		printf("Usage: number_of_philosophers[number] time_to_die[number] \n\
		time_to_eat[number] time_to_sleep[number]\n");
		exit(1);
	}
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
	return (0);
}
