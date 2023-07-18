/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:47:52 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/18 09:52:34 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf(PHILO_ERROR), ARG_ERROR);
	ft_bzero(&data, sizeof(t_data));
	if (init_data(ac, av, &data) != SUCCESS)
		return (ARG_ERROR);
	if (philo_init(&data) != SUCCESS)
		return (TH_ERR);
	return (SUCCESS);
}
