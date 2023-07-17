/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:06:33 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 16:50:15 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->stop == 0)
		printf("%d %d is thinking\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->data->print);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->stop == 0)
		printf("%d %d is sleeping\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->data->t_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->stop == 0)
	{
		pthread_mutex_unlock(&philo->data->death);
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
		printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
		printf("%d %d is eating\n", actual_time(philo), philo->number);
		pthread_mutex_unlock(&philo->data->print);
	}
	philo->last_meal = actual_time(philo);
	philo->meals_eaten++;
	ft_usleep(philo->data->t_eat);
	// pthread_mutex_unlock(&philo->data->philos[i].fork);
	// pthread_mutex_unlock(&philo->fork);
	// philo_sleep(philo);
}






int	mate_number(t_philo *philo)
{
	if (philo->number % 2 == 0)
	{
		if (philo->number == philo->data->philo_count)
			return (0);
		else
			return (philo->number);
	}
	else
	{
		if (philo->number == 0)
			return (philo->data->philo_count - 1);
		else
			return (philo->number);
	}
}

void	philo_grab_fork(t_philo *philo)
{
	int	i;

	i = mate_number(philo);
// printf("i = %d\nphil = %d\n\n", i, philo->number);
	if (philo->number % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->fork) == 0) //his
		{
			if (pthread_mutex_lock(&philo->data->philos[i].fork) == 0) // right
				philo_eat(philo);
		}
	}
	else
	{
		if (pthread_mutex_lock(&philo->data->philos[i].fork) == 0) // left
		{
			if (pthread_mutex_lock(&philo->fork) == 0) // his
				philo_eat(philo);
		}
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->data->philos[i].fork);
	philo_sleep(philo);
}
