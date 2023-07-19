/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:05:13 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/19 12:37:31 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

long long	get_time(void)
{
	long long		now;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (now);
}

void	ft_usleep(int i)
{
	long long	now;

	now = get_time();
	while (get_time() - now < i)
		usleep(i / 10);
}

int	actual_time(t_philo *philo)
{
	int	time;

	// pthread_mutex_lock(&philo->data->check);
	time = get_time() - philo->start_time;
	// pthread_mutex_unlock(&philo->data->check);
	return (time);
}
