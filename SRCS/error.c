/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:57:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 14:48:50 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	error_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) != 1)
				return (printf("Invalid argument\n"), INVALID_ARG);
			j++;
		}
		if (ft_atoi(av[i]) < 0)
			return (printf("Invalid negative argument\n"), INVALID_ARG);
		i++;
	}
	return (SUCCESS);
}
