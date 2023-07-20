/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:22:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/20 17:12:41 by rrebois          ###   ########lyon.fr   */
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

static void	ft_write_death(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	// pthread_mutex_lock(&philo->data->start);
	printf("%d %d %s\n", actual_time(philo), philo->number, s);
	// pthread_mutex_unlock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->print);
}

static int	check_eating_timer(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start);
	if (get_time() - philo->last_meal >= philo->p_die + philo->data->go)
		return (pthread_mutex_unlock(&philo->data->start), 1);
	else
		return (pthread_mutex_unlock(&philo->data->start), 0);
	// pthread_mutex_unlock(&data->start);
}

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->check);
	if (data->stop == 1)
		return (pthread_mutex_lock(&data->check), 1);
	pthread_mutex_unlock(&data->check);
	pthread_mutex_lock(&data->check);
	// pthread_mutex_lock(&data->start);
	while (i < data->philo_count)
	{
// printf("now: %d\n", actual_time(&data->philos[i]));
// printf("last meal: %d\n", data->philos[i].last_meal);
// printf("t2d: %d\n", data->philos[i].p_die);
		// check_meals(&data->philos[i]);

		if (check_eating_timer(&data->philos[i]) == 1 || data->stop == 1)
		{
			// check_meals(&data->philos[i]);
			if (data->stop == 0)
			{
				// pthread_mutex_unlock(&data->start);
				// pthread_mutex_unlock(&data->check);
				// pthread_mutex_lock(&data->check);
				data->stop = 1;
				pthread_mutex_unlock(&data->check);
				ft_write_death(&data->philos[i], " died");
				return (1);
			}
			else
				return (pthread_mutex_unlock(&data->check), 1);
		}

		i++;
	}
	// pthread_mutex_unlock(&data->start);
	pthread_mutex_unlock(&data->check);
	return (0);
}
