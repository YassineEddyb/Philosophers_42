/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:40:27 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/02/16 11:46:00 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo {
    pthread_t thread_id;
    int philo_id;
    int num_of_philos;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    pthread_mutex_t *forks;
    int *time_stamp;
    long int start_time;
    long int current_time;
    int long last_meal;
} t_philo;

int	ft_atoi(const char *str);
void eating(t_philo *philo);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);
void take_fork(t_philo *philo);
void dead (t_philo *philo, int s);
long int get_time();
long int is_about_to_die(t_philo *philo);

# endif