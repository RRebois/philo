/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:46:01 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/12 10:22:28 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define PHILO_ERROR "Philo error: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
	int				number;
	struct timeval	time;
	int				start_time;
	pthread_t		th;
	int				meals_eaten;
	pthread_mutex_t	*fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int		philo_count;
	int		t_eat;
	int		t_sleep;
	int		t_die;
	int		meals;
	t_philo	*philos;
}				t_data;

enum errors
{
	ARG_FAILURE = 1
};


/*	data.c	*/
int		init_data(int ac, char **av);

/*	utils.c	*/
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
int		convert_time(struct timeval time);

/*	routine.c	*/
void	*routine(void *philo);

#endif
