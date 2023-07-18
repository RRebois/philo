/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:09:43 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/18 07:56:34 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	init_data(char **av, t_data *data)
{
	int		i;

	i = 0;
	ft_bzero(data, sizeof(t_data));
	if (check_errors(av) != SUCCESS)
		return (ARG_ERROR);
	while (av[i])
	{
		if (ft_atoi(av[i]) < 0)
			return (printf("Invalid negative argument\n"), ARG_ERROR);
		i++;
	}
	if (set_data(av, &data) != SUCCESS)
		return (ERR_INIT_DATA);
	return (SUCCESS);
}

int	set_data(char **av, t_data *data)
{
	init_data_mutex(data);
	data.philo_count = ft_atoi(av[1]);
	data.t_die = ft_atoi(av[2]);
	data.t_eat = ft_atoi(av[3]);
	data.t_sleep = ft_atoi(av[4]);
	if (av[5])
		data.meals = ft_atoi(av[5]);
	if (data.meals == 0 && av[5])
		return (ARG_ERROR);
	data.philos = malloc(sizeof(t_philo) * data.philo_count);
	if (data.philos == NULL)
		return (MALLOC_ERR);
	// prepare_threads(&data);
	// free(data.philos);
	return (SUCCESS);
}

void	set_philo_data(t_data *data, int i, long long time)
{
	ft_bzero(&data->philos[i], sizeof(t_philo));
	data->philos[i].number = i + 1;
	data->philos[i].data = data;
	data->philos[i].max_meals = data->meals;
	data->philos[i].start_time = time;
}

int	philo_init(t_data *data)
{
	int			i;
	long long	time;

	i = 0;
	time = get_time();
	while (i < data->philo_count)
	{
		set_philo_data(data, i, time);
		pthread_mutex_init(&data->philos[i].fork, NULL);
		if (pthread_create(&data->philos[i].th, NULL, &routine, &data->philos[i]) != 0)
			return (TH_CRT);
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].th, NULL) != 0)
			return (TH_JN);
		i++;
	}
	return (SUCCESS);
}
