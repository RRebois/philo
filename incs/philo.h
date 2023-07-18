/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:46:01 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/18 13:35:53 by rrebois          ###   ########lyon.fr   */
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
	int				meals_eaten;
	int				max_meals;
	int				last_meal;
	long long		start_time;
	int				p_die;
	pthread_t		th;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				philo_count;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				meals;
	t_philo			*philos;
	int				food_count;
	int				go;
	int				stop;
	// pthread_mutex_t	start;
	pthread_mutex_t	check;
	// pthread_mutex_t	food;
	// pthread_mutex_t	print;
	// pthread_mutex_t	death;
}				t_data;

enum errors
{
	SUCCESS = 0,
	ARG_ERROR = 1,
	ERR_INIT_DATA = 2,
	MALLOC_ERR = 3,
	TH_ERR = 4,
	TH_CRT = 5,
	TH_JN = 6
};

/*	data.c	*/
int	init_data(int ac, char **av, t_data *data);
int	set_data(char **av, t_data *data);
int			prepare_threads(t_data *data);
int	philo_init(t_data *data);
void		set_philo_data(t_data *data, int i, long long time);

/*	utils.c	*/
void		solo_philo(t_philo *philo);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);

/*	routine.c	*/
void		*routine(void *philo_struct);
void		routine_loop(t_philo *philo);
void		check_meals(t_philo *philo);
int			mate_number(t_philo *philo);

/*	actions.c	*/
void		philo_think(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);

/*	time.c	*/
long long	get_time(void);
void		ft_usleep(int i);
int			actual_time(t_philo *philo);

/*	death.c	*/
void		check_death(t_data *data);
void	death_loop(t_data *data);
/*	mutex.c	*/
void		init_data_mutex(t_data *data);
void		destroy_data_mutex(t_data *data);

#endif
