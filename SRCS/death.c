/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:22:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 09:04:54 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (actual_time(philo) - philo->last_meal >= philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->death);
		pthread_mutex_lock(&philo->data->print);
		if (philo->data->stop == 0)
			printf("%d %d died\n", actual_time(philo), philo->number);
		pthread_mutex_unlock(&philo->data->print);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (NULL);
	}
	return (NULL);
}
