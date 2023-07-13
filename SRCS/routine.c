/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 07:50:38 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/13 13:27:34 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philo *philo)
{
	if (philo->max_meals <= 0)
		return (0);
	pthread_mutex_unlock(&philo->data->food);
	if (philo->meals_eaten == philo->max_meals)
	{
		pthread_mutex_lock(&philo->data->food);
		philo->data->food_count++;
		pthread_mutex_unlock(&philo->data->food);
	}
	pthread_mutex_lock(&philo->data->food);
	if (philo->data->food_count == philo->data->philo_count)
	{
		pthread_mutex_unlock(&philo->data->food);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->food);
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	while (check_death(philo) != 1)
	{
		if (philo->data->philo_count == 1)
		{
			solo_philo(philo);
			return (NULL);
		}
		if (philo->number % 2 == 0)
			usleep(philo->data->t_eat / 2);
		if (check_death(philo) == 0)
			philo_eat(philo);
		if (check_meals(philo) == 1)
			return (NULL);
		// philo_sleep(philo);
	}
	return (NULL);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->stop == 0)
		printf("%d %d is sleeping\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->data->t_sleep);
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->stop == 0)
		printf("%d %d is thinking\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->death);
}

void	philo_eat(t_philo *philo)
{
	int	i;

	i = mate_number(philo);
	if (pthread_mutex_lock(&philo->fork) == 0 && \
	pthread_mutex_lock(&philo->data->philos[i].fork) == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
		printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
		printf("%d %d is eating\n", actual_time(philo), philo->number);
		philo->last_meal = actual_time(philo);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->print);
		ft_usleep(philo->data->t_eat);
		pthread_mutex_unlock(&philo->data->philos[i].fork);
		pthread_mutex_unlock(&philo->fork);
	}
	philo_sleep(philo);
}

int	mate_number(t_philo *philo)
{
	if (philo->number < philo->data->philo_count)
		return (philo->number);
	else
		return (0);
}
