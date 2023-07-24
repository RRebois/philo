/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:43:15 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/24 08:31:52 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	ft_write(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->stop == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		// pthread_mutex_lock(&philo->data->start);
		printf("%d %d %s\n", actual_time(philo), philo->number, s);
		// pthread_mutex_unlock(&philo->data->start);
		pthread_mutex_unlock(&philo->data->print);
	}
	// else if (philo->data->stop == 0 && ((philo->meals_eaten) || ()))
	// {
	// 	printf("%d %d %s\n", actual_time(philo), philo->number, s);
	// }
	pthread_mutex_unlock(&philo->data->check);
}

void	grab_forks(t_philo *philo)
{
	if (philo->number % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->fork_l) == 0)
		{
			ft_write(philo, " has taken a fork");
			if (pthread_mutex_lock(philo->fork_r) == 0)
				ft_write(philo, " has taken a fork");
		}
	}
	else
	{
		if (pthread_mutex_lock(philo->fork_r) == 0)
		{
			ft_write(philo, " has taken a fork");
			if (pthread_mutex_lock(&philo->fork_l) == 0)
				ft_write(philo, " has taken a fork");
		}
	}
}

// void	grab_forks(t_philo *philo)
// {
// 	if (philo->fork_av == 1)
// 	{
// 		pthread_mutex_lock(&philo->fork_l);
// 		philo->fork_av == 0;
// 		pthread_mutex_unlock(&philo->fork_l);

// 	}
// }

void	philo_cycle(t_philo *philo)
{
	ft_write(philo, " is eating");
	// ft_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->start);
	philo->last_meal = get_time() - philo->data->go;
	// philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->start);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	update_philo_meals_eaten(philo);
	ft_write(philo, " is sleeping");
	ft_usleep(philo->data->t_sleep);
}
