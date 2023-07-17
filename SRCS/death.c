/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:22:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 15:25:48 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	check_death(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->philo_count)
	{
		j = 0;
		if (i == data->philo_count - 1)
			i = 0;
		if (data->stop == 1)
			break ;
		pthread_mutex_lock(&data->philos[i].philo_meal);
		if (actual_time(&data->philos[i]) - data->philos[i].last_meal >= data->philos[i].pdie)
		{
			pthread_mutex_lock(&data->death);
			pthread_mutex_lock(&data->print);
			if (data->stop == 0)
				printf("%d %d died\n", actual_time(&data->philos[i]), data->philos[i].number);
			pthread_mutex_unlock(&data->print);
			data->stop = 1;
			pthread_mutex_unlock(&data->death);
			while (j < data->philo_count)
			{
				data->philos[j].end = 1;
				j++;
			}
		}
		pthread_mutex_unlock(&data->philos[i].philo_meal);
		i++;
	}
}
