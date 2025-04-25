/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:14:35 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/25 21:22:27 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	simulation_should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->simulation_lock);
	stop = data->simulation_running == 0;
	pthread_mutex_unlock(&data->simulation_lock);
	return (stop);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->simulation_lock);
	data->simulation_running = 0;
	pthread_mutex_unlock(&data->simulation_lock);
}

int	all_philos_ate_enough(t_data *data)
{
	int	i;
	int	count;

	if (data->max_meals <= 0)
		return (0);

	i = 0;
	count = 0;
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_count >= data->max_meals)
			count++;
		i++;
	}
	return (count == data->nb_philo);
}

int	check_philos_status(t_data *data)
{
	int	i;
	long	now;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].state_lock);
		now = get_timestamp();
		if ((now - data->philos[i].last_meal) > data->time_to_die)
		{
			print_state(&data->philos[i], DEAD);
			stop_simulation(data);
			pthread_mutex_unlock(&data->philos[i].state_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].state_lock);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data = (t_data *)arg;

	while (!simulation_should_stop(data))
	{
		if (check_philos_status(data))
			return (NULL);
		if (all_philos_ate_enough(data))
		{
			stop_simulation(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
