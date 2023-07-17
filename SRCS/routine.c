/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 07:50:38 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 16:10:16 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->max_meals <= 0)
		return ;
	if (philo->meals_eaten == philo->max_meals)
	{
		pthread_mutex_lock(&philo->data->food);
		philo->data->food_count++;
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->food);
	}
	pthread_mutex_lock(&philo->data->food);
	if (philo->data->food_count == philo->data->philo_count)
	{
		philo->data->philos[i].end = 1;
		i++;
	}
	pthread_mutex_unlock(&philo->data->food);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	while (1)
	{
		pthread_mutex_lock(&philo->data->start);
		if (philo->data->go != -1)
		{
			pthread_mutex_unlock(&philo->data->start);
			break ;
		}
		pthread_mutex_unlock(&philo->data->start);
	}
	if (philo->data->philo_count == 1)
	{
		solo_philo(philo);
		return (NULL);
	}
	if (philo->number % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->philo_meal);
		if (philo->end != 0)
			return (pthread_mutex_unlock(&philo->philo_meal), NULL);
		pthread_mutex_unlock(&philo->philo_meal);
		philo_think(philo);
		philo_grab_fork(philo);
	}
	return (NULL);
}
