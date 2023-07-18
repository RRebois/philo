/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 07:50:38 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/18 14:27:26 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	if (philo->max_meals <= 0)
	{
		pthread_mutex_unlock(&philo->data->check);
		return ;
	}

	if (philo->meals_eaten == philo->max_meals)
	{
		philo->data->food_count++;
		philo->meals_eaten++;
	}
	if (philo->data->food_count == philo->data->philo_count)
		philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->check);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (philo->data->philo_count == 1)
	{
		solo_philo(philo);
		return (NULL);
	}
	if (philo->number % 2 == 0)
		usleep(philo->data->t_eat / 10);
	while (1)
	{
		pthread_mutex_lock(&philo->data->check);
		if (philo->data->stop == 1)
		{
			printf("philo %d stopped\n", philo->number);
			return (pthread_mutex_unlock(&philo->data->check), NULL);
		}

		pthread_mutex_unlock(&philo->data->check);
		philo_think(philo);
		philo_eat(philo);
	}
	return (NULL);
}
