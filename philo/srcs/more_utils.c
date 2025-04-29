/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:08:34 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/27 18:52:21 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(t_data *data, unsigned long sleep_time)
{
	unsigned long	start_time;

	start_time = get_time() * 1000;
	while ((get_time() * 1000) - start_time < sleep_time)
	{
		if (get_safe_flag(&data->data_lock, &data->simulation_end))
			break ;
		usleep(25);
	}
}

long	get_safe_value(pthread_mutex_t *mutex, long *value)
{
	long	safe_value;

	pthread_mutex_lock(mutex);
	safe_value = *value;
	pthread_mutex_unlock(mutex);
	return (safe_value);
}

int	thread_active(pthread_mutex_t *mutex, long *value, long nb_philo)
{
	int	active;

	active = 0;
	pthread_mutex_lock(mutex);
	if (*value == nb_philo)
		active = 1;
	pthread_mutex_unlock(mutex);
	return (active);
}

void	increment_value(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}
