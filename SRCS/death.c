/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:22:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/19 13:38:49 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	death_loop(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->check);
	i = 0;
	// pthread_mutex_unlock(&data->check);
	while (i == 0)
	{
		check_death(data);
		pthread_mutex_lock(&data->check);
		i = data->stop;
// printf("i=%d\n", i);
		pthread_mutex_unlock(&data->check);
		if (i == 1)
			return (i);
	}
	return (0);
}

// int	check_death(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->check);
// 		if (data->stop == 1)
// 		{
// 			pthread_mutex_unlock(&data->check);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(&data->check);
// 		pthread_mutex_lock(&data->check);
// 		if (actual_time(&data->philos[i]) - data->philos[i].last_meal >= data->philos[i].p_die)
// 		{
// 			if (data->stop == 0)
// 				printf("%d %d died\n", actual_time(&data->philos[i]), data->philos[i].number);
// 			data->stop = 1;
// 			return (pthread_mutex_unlock(&data->check), 1);
// 		}
// 		pthread_mutex_unlock(&data->check);
// 	}
// 	return (SUCCESS);
// }


void	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->check);
		if (data->stop == 1)
		{
			pthread_mutex_lock(&data->check);
			return ;
		}
		pthread_mutex_unlock(&data->check);
		pthread_mutex_lock(&data->check);
		if (actual_time(&data->philos[i]) - data->philos[i].last_meal >= data->philos[i].p_die)
		{
			if (data->stop == 0)
				ft_write(&data->philos[i], " died");
			data->stop = 1;
// printf("ii=%d\n", data->stop);
			pthread_mutex_unlock(&data->check);
			return ;
		}
		pthread_mutex_unlock(&data->check);
	}
}
