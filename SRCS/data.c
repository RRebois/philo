/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:09:43 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/13 17:00:44 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.philo_count = ft_atoi(av[1]);
	data.t_die = ft_atoi(av[2]);
	data.t_eat = ft_atoi(av[3]);
	data.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.meals = ft_atoi(av[5]);
	data.philos = malloc(sizeof(t_philo) * data.philo_count);
	if (data.philos == NULL)
		return (-1); // a changer
	prepare_threads(&data);
	free(data.philos);
	return (0);
}

void	init_philo_data(t_data *data, int i)
{
	ft_bzero(&data->philos[i], sizeof(t_philo));
	data->philos[i].number = i + 1;
	data->philos[i].data = data;
	data->philos[i].max_meals = data->meals;
}

int	prepare_threads(t_data *data)
{
	int	i;

	init_fork_mutex(data);
	i = 0;
	while (i < data->philo_count)
	{
		init_philo_data(data, i);
		if (pthread_create(&data->philos[i].th, NULL, &routine, &data->philos[i]) != 0)
			return (-1);
		i++;
	}
	pthread_mutex_lock(&data->start);
	data->go = 1;
	pthread_mutex_unlock(&data->start);
	while (i > 0)
	{
		if (pthread_join(data->philos[i - 1].th, NULL) != 0)
			return (-1);
		i--;
	}
	destroy_fork_mutex(data);
	return (0);
}
