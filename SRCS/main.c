/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:47:52 by rrebois           #+#    #+#             */
/*   Updated: 2023/07/17 22:07:52 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf(PHILO_ERROR), ARG_ERROR);
	ft_bzero(&data, sizeof(t_data));
	if (init_data(av, &data) != SUCCESS)
		return (ARG_ERROR);
	if (philo_init(data) != SUCCESS)
		return (TH_ERR);
	destroy_data_mutex(data); // + remains to destroy fork mutexes
	return (SUCCESS);
}
