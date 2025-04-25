/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:08:34 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/25 21:16:34 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) != 0)
		return (1);
	data.simulation_running = 1;
	pthread_mutex_init(&data.simulation_lock, NULL);
	pthread_mutex_init(&data.print_lock, NULL);
	if (start_simulation(&data) != 0)
		return (1);
	free_all(&data);
	return (0);
}
