/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:06:33 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 16:20:06 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	mate_number(t_philo *philo)
{
	int	i;

	if (philo->number % 2 == 0)
	{
		if (i == philo->data->philo_count)
			return (0);
		else
			return (i);
	}
	else
	{
		if (i == 0)
			return (philo->data->philo_count);
		else
			return (i - 1);
	}
}

void	philo_grab_fork(t_philo *philo)
{
	int	i;

	i = mate_number(philo);
	if (philo->number % 2 == 0)
	{
		if (phread_mutex_lock(&philo->fork) == 0) //his
		{
			if (phread_mutex_lock(&philo->data->philos[i].fork) == 0) // right
				philo_eat(philo);
		}
	}
	else
	{
		if (phread_mutex_lock(&philo->data->philos[i].fork) == 0) // left
		{
			if (phread_mutex_lock(&philo->fork) == 0) // his
				philo_eat(philo);
		}
	}
	phread_mutex_unlock(&philo->fork);
	phread_mutex_unlock(&philo->data->philos[i].fork);
}
