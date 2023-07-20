/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 07:50:38 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/20 17:26:07 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	update_philo_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->max_meals)
		philo->data->food_count++;
	pthread_mutex_unlock(&philo->data->check);
}

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
	// if (data->philos[i].meals_eaten == data->philos[i].max_meals)
	// {
	// 	data->food_count++;
	// 	data->philos[i].meals_eaten++;
	// }
	if (data->food_count == data->philo_count)
	{
		// ft_usleep(data->t_eat);
		data->stop = 1;
		pthread_mutex_unlock(&data->check);
		return (1);
	}
	i++;
	pthread_mutex_unlock(&data->check);
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
// printf("routine\n");
	philo = (t_philo *)philo_struct;
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->start);
	// pthread_mutex_lock(&philo->data->start);
	// philo->last_meal = get_time() - philo->data->go;
	// pthread_mutex_unlock(&philo->data->start);
	if (philo->data->philo_count == 1)
	{
		solo_philo(philo);
		return (NULL);
	}
	// if (philo->data->philo_count % 2 != 0 && philo->number == philo->data->philo_count)
	// 	usleep(philo->data->t_eat);
	// if (philo->number % 2 != 0)
	// 	usleep(philo->data->t_eat);
	// ft_usleep((1 * philo->number) % 2);
	while (check_stop(philo) == 0)
	{
		ft_usleep((1 * philo->number) % 2);
		// if (philo->data->philo_count % 2 != 0 && philo->number == philo->data->philo_count)
			// ft_usleep(philo->data->t_eat);
		// ft_usleep(10);
		// ft_usleep(1 * philo->number);
		ft_write(philo, " is thinking");
		// ft_usleep(10);
		grab_forks(philo);
		philo_cycle(philo);
		//si t2e != t2s maybe ft_usleep de la diff
	}
	return (NULL);
}
