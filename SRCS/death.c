/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:22:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/20 09:39:59 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

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

// static void	ft_write_death(t_philo *philo, char *s)
// {
// 	pthread_mutex_lock(&philo->data->print);
// 	printf("%d %d %s\n", actual_time(philo), philo->number, s);
// 	pthread_mutex_unlock(&philo->data->print);
// }

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->check);
	if (data->stop == 1)
	{
		pthread_mutex_lock(&data->check);
		return (1);
	}
	pthread_mutex_unlock(&data->check);
	pthread_mutex_lock(&data->check);
	while (i < data->philo_count)
	{
		// check_meals(&data->philos[i]);
		if (actual_time(&data->philos[i]) - data->philos[i].last_meal >= data->philos[i].p_die || data->stop == 1)
		{
			// check_meals(&data->philos[i]);
			if (data->stop == 0)
			{
				pthread_mutex_unlock(&data->check);
				ft_write(&data->philos[i], " died");
				pthread_mutex_lock(&data->check);
				data->stop = 1;
				pthread_mutex_unlock(&data->check);
				return (1);
			}
			else
				return (pthread_mutex_unlock(&data->check), 1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->check);
	return (0);
}
