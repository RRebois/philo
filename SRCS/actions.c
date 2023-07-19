/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:43:15 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/19 13:38:59 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	ft_write(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->check);
	if (philo->data->stop == 0)
	{
		pthread_mutex_unlock(&philo->data->check);
		printf("%d %d %s\n", actual_time(philo), philo->number, s);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check);
	pthread_mutex_unlock(&philo->data->print);
}

void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	ft_write(philo, " has taken a fork");
	pthread_mutex_lock(philo->fork_r);
	ft_write(philo, " has taken a fork");
}

void	philo_cycle(t_philo *philo)
{
	ft_write(philo, " is eating");
	pthread_mutex_lock(&philo->data->check);
	philo->last_meal = actual_time(philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->check);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	ft_write(philo, " is sleeping");
	ft_usleep(philo->data->t_sleep);
	ft_write(philo, " is thinking");
	// if (philo->number % 2 == 0)
	// {
	// 	pthread_mutex_unlock(&philo->fork_l);
	// 	pthread_mutex_unlock(philo->fork_r);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(philo->fork_r);
	// 	pthread_mutex_unlock(&philo->fork_l);
	// }

}
