/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:09:43 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/20 17:03:07 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static int	check_errors(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (100);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	ft_bzero(data, sizeof(t_data));
	if (check_errors(ac, av) != SUCCESS)
		return (printf("Invalid argument\n"), ARG_ERROR);
	while (av[i])
	{
		if (ft_atoi(av[i]) < 0)
			return (printf("Invalid negative argument\n"), ARG_ERROR);
		i++;
	}
	if (set_data(av, data) != SUCCESS)
		return (printf("Error initializing data\n"), ERR_INIT_DATA);
	return (SUCCESS);
}

int	set_data(char **av, t_data *data)
{
	int			i;

	i = 0;
	pthread_mutex_init(&data->check, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->start, NULL);
	data->philo_count = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals = ft_atoi(av[5]);
	if (data->meals == 0 && av[5])
		return (ARG_ERROR);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (data->philos == NULL)
		return (MALLOC_ERR);
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->philos[i].fork_l, NULL);
		i++;
	}
	return (SUCCESS);
}

void	set_philo_data(t_data *data, int i)
{
	ft_bzero(&data->philos[i], sizeof(t_philo));
	data->philos[i].number = i + 1;
	data->philos[i].p_die = data->t_die;
	data->philos[i].data = data;
	// data->philos[i].last_meal = 0; //
	data->philos[i].max_meals = data->meals;
	if (i == data->philo_count - 1)
		data->philos[i].fork_r = &data->philos[0].fork_l;
	else
		data->philos[i].fork_r = &data->philos[i + 1].fork_l;
}

int	philo_init(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->philo_count)
		set_philo_data(data, i);
	i = 0;
	pthread_mutex_lock(&data->start);
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].th, NULL, &routine, &data->philos[i]) != 0)
			return (TH_CRT);
		i++;
	}
	pthread_mutex_unlock(&data->start);
	data->go = get_time();
// printf("start\n");
	while (check_death(data) == 0 && check_meals(data) == 0)
		continue ;
	i = 0;
// printf("end\n");
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].th, NULL) != 0)
			return (TH_JN);
		i++;
	}
	free_destroy_all(data);
	return (SUCCESS);
}
