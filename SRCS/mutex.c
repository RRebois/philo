/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:42:15 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/13 15:57:05 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->food, NULL);
	pthread_mutex_init(&data->start, NULL);
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->philos[i].fork, NULL);
		i++;
	}
}

void	destroy_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->food);
	pthread_mutex_destroy(&data->start);
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philos[i].fork);
		i++;
	}
}
