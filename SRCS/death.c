/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:22:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 21:40:08 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	check_death(t_philo *philo)
{
	if (actual_time(philo) - philo->last_meal >= philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->death);
		pthread_mutex_lock(&philo->data->print);
		if (philo->data->stop == 0)
			printf("%d %d died\n", actual_time(philo), philo->number);
		pthread_mutex_unlock(&philo->data->print);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	return (0);
}
