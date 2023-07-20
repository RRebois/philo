/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 07:50:38 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/20 11:27:11 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	check_meals(t_data *data)
{
	// pthread_mutex_lock(&philo->data->check);
	// if (philo->data->stop == 1)
	// {
	// 	pthread_mutex_unlock(&philo->data->check);
	// 	return ;
	// }
// pthread_mutex_unlock(&philo->data->check);
int	i;

i = 0;
while (i < data->philo_count)
{
	pthread_mutex_lock(&data->check);
	if (data->philos[i].max_meals <= 0)
	{
		pthread_mutex_unlock(&data->check);
		return (0);
	}
	if (data->philos[i].meals_eaten == data->philos[i].max_meals)
	{
		data->food_count++;
		data->philos[i].meals_eaten++;
	}
	if (data->food_count == data->philo_count)
	{
		data->stop = 1;
		pthread_mutex_unlock(&data->check);
		return (1);
	}
	i++;pthread_mutex_unlock(&data->check);
}

	return (0);
}

int	check_stop(t_philo *philo)
{
	// check_meals(philo);
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->stop == 0)
		return (pthread_mutex_unlock(&philo->data->check), 0);
	else
		return (pthread_mutex_unlock(&philo->data->check), 1);
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
	while (check_stop(philo) == 0)
	{
		if (philo->number % 2 == 0)
			usleep(1);
		ft_write(philo, " is thinking");
		grab_forks(philo);
		philo_cycle(philo);
	}
	return (NULL);
}
