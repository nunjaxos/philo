/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:54:46 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/25 18:56:46 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->pos % 2)
		usleep(100);
	while (1)
	{
		print_state(philo, THINKING);
		pthread_mutex_lock(philo->fork1_mutex);
		print_state(philo, FORK1);
		pthread_mutex_lock(philo->fork2_mutex);
		print_state(philo, FORK2);
		pthread_mutex_lock(&philo->state_lock);
		philo->last_meal = get_timestamp();
		pthread_mutex_unlock(&philo->state_lock);
		print_state(philo, EATING);
		usleep(philo->data->time_to_eat * 1000);
		philo->meals_count++;
		pthread_mutex_unlock(philo->fork2_mutex);
		pthread_mutex_unlock(philo->fork1_mutex);
		print_state(philo, SLEEPING);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

void	print_state(t_philo *philo, t_state state)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->print_lock);
	current_time = get_timestamp();
	if (state == THINKING)
		printf("%ld %d is thinking;)\n", current_time, philo->pos);
	else if (state == FORK1)
		printf("%ld %d has taken a fork:)\n", current_time, philo->pos);
	else if (state == FORK2)
		printf("%ld %d has taken a fork:)\n", current_time, philo->pos);
	else if (state == EATING)
		printf("%ld %d is eating:)\n", current_time, philo->pos);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping:|\n", current_time, philo->pos);
	else if (state == DEAD)
		printf("%ld %d is dead:x\n", current_time, philo->pos);

	pthread_mutex_unlock(&philo->data->print_lock);
}

long	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}