/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:09:43 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/12 10:38:45 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int ac, char **av)
{
	int		i;
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
	i = 0;
	while (i < ac)
	{
		if (pthread_create(&data.philos[i].th, NULL, &routine, &data.philos[i]) != 0)
			return (-1);
		gettimeofday(&data.philos[i].time, NULL);
		data.philos[i].start_time = convert_time(data.philos[i].time);
		data.philos[i].number = i + 1;
		pthread_mutex_init(&data.philos[i].fork, NULL);
		i++;
	}
	i = 0;
	while (i < ac)
	{
		if (pthread_join(data.philos[i].th, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
