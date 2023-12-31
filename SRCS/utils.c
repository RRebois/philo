/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:12:37 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/18 15:03:35 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == 43 || c == 45)
		return (1);
	return (0);
}

void	solo_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	printf("%d %d has taken a fork\n", actual_time(philo), philo->number);
	pthread_mutex_unlock(&philo->fork_l);
	ft_usleep(philo->data->t_die);
	// printf("%d %d died\n", actual_time(&philo->data->philos[0]), philo->data->philos[0].number);
	pthread_mutex_lock(&philo->data->check);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->check);
}

static void	ft_check(long value, long sign)
{
	if (value * sign > 0 && value * sign > 2147483647)
	{
		exit (0);
	}
	else if (value * sign < 0 && value * sign < -2147483648)
	{
		exit (0);
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	long	value;
	long	sign;

	i = 0;
	value = 0;
	sign = 1;
	while (str[i] != '\0')
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == 45)
			sign *= -1;
		if (str[i] == 43 || str[i] == 45)
			i++;
		while (str[i] >= 48 && str[i] <= 57)
		{
			value = value * 10 + (str[i] - '0');
			ft_check(value, sign);
			i++;
		}
		return ((int)sign * value);
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}
