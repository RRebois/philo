/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:05:13 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 09:05:25 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long		now;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (now);
}

void	ft_usleep(int i, t_philo *philo)
{
	long long	now;(void)philo;

	now = get_time();
	while (get_time() - now < i)
	{
		usleep(i / 10);
	}

}

int	actual_time(t_philo *philo)
{
	return (get_time() - philo->start_time);
}
