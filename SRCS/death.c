/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:22:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/18 09:53:52 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (data->stop == 1)
			return ;
		pthread_mutex_lock(&data->death);
		if (actual_time(&data->philos[i]) - data->philos[i].last_meal >= data->t_die)
		{
			pthread_mutex_lock(&data->print);
			if (data->stop == 0)
				printf("%d %d died\n", actual_time(&data->philos[i]), data->philos[i].number);
			pthread_mutex_unlock(&data->print);
			data->stop = 1;
			i++;
		}
		pthread_mutex_unlock(&data->death);
	}
}
