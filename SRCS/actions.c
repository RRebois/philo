/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:43:15 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/18 13:44:06 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->stop == 0)
		printf("%d %d is thinking\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->data->check);
}

void	philo_sleep(t_philo *philo)
{check_meals(philo);
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->stop == 0)
		printf("%d %d is sleeping\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->data->check);
	ft_usleep(philo->data->t_sleep);

}

static void	grab_forks_even(t_philo *philo)
{

	if (pthread_mutex_lock(&philo->fork_l) == 0)
	{pthread_mutex_lock(&philo->data->check);
		if (philo->data->stop == 0)
		{pthread_mutex_unlock(&philo->data->check);
			printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
			if (pthread_mutex_lock(philo->fork_r) == 0)
				printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
		}
	}

}

static void	grab_forks_odd(t_philo *philo)
{

	if (pthread_mutex_lock(philo->fork_r) == 0)
	{pthread_mutex_lock(&philo->data->check);
		if (philo->data->stop == 0)
		{pthread_mutex_unlock(&philo->data->check);
			printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
			if (pthread_mutex_lock(&philo->fork_l) == 0)
				printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
		}
	}

}

void	philo_eat(t_philo *philo)
{
	if (philo->number % 2 == 0)
		grab_forks_even(philo);
	else
		grab_forks_odd(philo);
	pthread_mutex_lock(&philo->data->check);
	printf("%d %d is eating\n", actual_time(philo), philo->number);
	philo->last_meal = actual_time(philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->check);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	// if (philo->number % 2 == 0)
	// {
	// 	pthread_mutex_unlock(&philo->fork_l);
	// 	pthread_mutex_unlock(philo->fork_r);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(philo->fork_r);
	// 	pthread_mutex_unlock(&philo->fork_l);
	// }
	philo_sleep(philo);
}
