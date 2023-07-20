/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:11:43 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/19 12:11:43 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	free_destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philos[i].fork_l);
		pthread_mutex_destroy(data->philos[i].fork_r);
		i++;
	}
	pthread_mutex_destroy(&data->check);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->start);
	free(data->philos);

}
