/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:27:50 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/27 18:52:01 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_mutex(t_philo *philo, pthread_mutex_t *forks, int i)
{
	int	nb;

	nb = philo->data->nb_philo;
	philo->fork1_mutex = &forks[(i + 1) % nb];
	philo->fork2_mutex = &forks[i];
	if (i % 2 == 0)
	{
		philo->fork1_mutex = &forks[i];
		philo->fork2_mutex = &forks[(i + 1) % nb];
	}
}

static void	ft_philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].meals_count = 0;
		data->philos[i].pos = i + 1;
		data->philos[i].flag = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].state_lock, NULL);
		init_mutex(&data->philos[i], data->forks, i);
	}
}

int	init(t_data *data)
{
	int	i;

	i = -1;
	data->simulation_end = 0;
	data->thread_flag = 0;
	data->thread_active = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		free(data->philos);
		return (1);
	}
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (free(data->philos), free(data->forks), 1);
	}
	if (pthread_mutex_init(&data->data_lock, NULL)
		|| pthread_mutex_init(&data->print_lock, NULL))
		return (free(data->philos), free(data->forks), 1);
	ft_philo_init(data);
	return (0);
}
