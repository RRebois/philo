/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:47:52 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/29 14:06:28 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int			i;
	t_philo	philo;

	i = 0;
	if (ac != 5 && ac != 6)
		return (printf(PHILO_ERROR), ARG_FAILURE);
	while (i < ac)
	{
		pthread_create(philo, );
	}
}
