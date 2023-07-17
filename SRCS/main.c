/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:47:52 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 14:50:26 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf(PHILO_ERROR), ARG_FAILURE);
	if (error_check(ac, av) != SUCCESS)
		return (INVALID_ARG);
	init_data(ac, av);
	return (SUCCESS);
}
