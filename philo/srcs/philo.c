/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:08:34 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/27 18:53:18 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	data.max_meals = -1;
	data.simulation_end = 0;
	if (param_parse(&data, argv))
		return (1);
	if (init(&data))
		return (1);
	if (simulation_start(&data))
		return (1);
	if (exiting(&data))
		return (1);
	cleanup(&data);
	return (0);
}
