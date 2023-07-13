/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:43:15 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/13 17:59:59 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->stop == 0)
		printf("%d %d is thinking\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->data->print);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->stop == 0)
		printf("%d %d is sleeping\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->data->t_sleep, philo);
	philo_think(philo);
}

void	philo_eat(t_philo *philo)
{
	int	i;
// printf("\nphilo[%d] meals eaten: %d\n\n", philo->number, philo->meals_eaten);
	i = mate_number(philo);
	if (pthread_mutex_lock(&philo->fork) == 0 && \
	pthread_mutex_lock(&philo->data->philos[i].fork) == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
		printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
		printf("%d %d is eating\n", actual_time(philo), philo->number);
		pthread_mutex_unlock(&philo->data->print);
		philo->last_meal = actual_time(philo);
		philo->meals_eaten++;
		check_meals(philo);
		ft_usleep(philo->data->t_eat, philo);
		pthread_mutex_unlock(&philo->data->philos[i].fork);
		pthread_mutex_unlock(&philo->fork);
	}
	// if (check_meals(philo) == 0)
	// 	philo_sleep(philo);
}
