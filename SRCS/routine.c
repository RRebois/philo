/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 07:50:38 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/13 17:58:50 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philo *philo)
{
	if (philo->max_meals <= 0)
		return (0);
	if (philo->meals_eaten == philo->max_meals)
	{
// printf("philo meals: %d %d\n", philo->meals_eaten, philo->max_meals);
		pthread_mutex_lock(&philo->data->food);
		philo->data->food_count++;
		pthread_mutex_unlock(&philo->data->food);
	}
	if (philo->data->food_count == philo->data->philo_count)
		return (1);
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	while (philo->data->go != 1)
		continue ;
	philo->start_time = get_time();
	if (philo->data->philo_count == 1)
	{
		solo_philo(philo);
		return (NULL);
	}
	if (philo->number % 2 == 0)
		usleep(500);
	while (check_death(philo) != 1 || philo->data->food_count != philo->data->philo_count)
	{
// printf("%d %d\n", philo->data->food_count, philo->data->philo_count);
		if (philo->data->food_count == philo->data->philo_count)
			break ;
		philo_think(philo);
		if (check_death(philo) == 0)
			philo_eat(philo);
		if (philo->data->food_count == philo->data->philo_count)
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}

int	mate_number(t_philo *philo)
{
	if (philo->number < philo->data->philo_count)
		return (philo->number);
	else
		return (0);
}
