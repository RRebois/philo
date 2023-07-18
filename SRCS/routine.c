/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 07:50:38 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/18 10:03:58 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	check_meals(t_philo *philo)
{
	if (philo->max_meals <= 0)
		return ;
	if (philo->meals_eaten == philo->max_meals)
	{
		pthread_mutex_lock(&philo->data->food);
		philo->data->food_count++;
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->food);
	}
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->food_count == philo->data->philo_count)
		philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->death);
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
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->stop == 1)
			return (pthread_mutex_unlock(&philo->data->death), NULL);
		pthread_mutex_unlock(&philo->data->death);
		philo_think(philo);
		philo_eat(philo);
	}
	return (NULL);
}
