/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:27:50 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/25 21:34:10 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_one_philo(t_philo *philo, int i, t_data *data)
{
	philo->pos = i;
	philo->meals_count = 0;
	philo->flag = 0;
	philo->data = data;
	philo->last_meal = 0;
	pthread_mutex_init(&philo->state_lock, NULL);
	philo->fork1_mutex = &data->forks[i];
	philo->fork2_mutex = &data->forks[(i + 1) % data->nb_philo];
}

int	init_philos(t_data *data)
{
	int	i;

	if (init_forks(data))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		init_one_philo(&data->philos[i], i, data);
		i++;
	}
	return (0);
}

