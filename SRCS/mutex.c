/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:42:15 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 21:42:24 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	init_data_mutex(t_data *data)
{
	// int	i;

	// i = 0;
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->food, NULL);
	pthread_mutex_init(&data->start, NULL);
	// while (i < data->philo_count)
	// {
	// 	pthread_mutex_init(&data->philos[i].fork, NULL);
	// 	i++;
	// }
}

void	destroy_data_mutex(t_data *data)
{
	// int	i;

	// i = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->food);
	pthread_mutex_destroy(&data->start);
	// while (i < data->philo_count)
	// {
	// 	pthread_mutex_destroy(&data->philos[i].fork);
	// 	i++;
	// }
}
