/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:54:46 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/27 18:52:39 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_safe_flag(&philo->data->data_lock, &philo->data->thread_flag))
		;
	update_long_value(&philo->state_lock, &philo->last_meal, get_time());
	increment_value(&philo->data->data_lock, &philo->data->thread_active);
	print_state(philo, FORK1);
	while (!simulation_end(philo->data))
		usleep(100);
	return (NULL);
}

void	print_state(t_philo *philo, t_state state)
{
	if (get_safe_flag(&philo->state_lock, &philo->flag))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	if ((state == FORK1 || state == FORK2)
		&& !(get_safe_flag(&philo->data->data_lock,
				&philo->data->simulation_end)))
		printf("%ld %d has taken a fork\n", get_time()
			- philo->data->start_time, philo->pos);
	else if (state == EATING && !(get_safe_flag(&philo->data->data_lock,
				&philo->data->simulation_end)))
		printf("%ld %d is eating\n", get_time() - philo->data->start_time,
			philo->pos);
	else if (state == SLEEPING && !(get_safe_flag(&philo->data->data_lock,
				&philo->data->simulation_end)))
		printf("%ld %d is sleeping\n", get_time() - philo->data->start_time,
			philo->pos);
	else if (state == THINKING && !(get_safe_flag(&philo->data->data_lock,
				&philo->data->simulation_end)))
		printf("%ld %d is thinking\n", get_time() - philo->data->start_time,
			philo->pos);
	else if (state == DEAD)
		printf("%ld %d died\n", get_time() - philo->data->start_time,
			philo->pos);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1_mutex);
	print_state(philo, FORK1);
	pthread_mutex_lock(philo->fork2_mutex);
	print_state(philo, FORK2);
	update_long_value(&philo->state_lock, &philo->last_meal, get_time());
	philo->meals_count++;
	print_state(philo, EATING);
	ft_sleep(philo->data, philo->data->time_to_eat);
	if (philo->data->max_meals != -1
		&& philo->meals_count == philo->data->max_meals)
		update_value(&philo->state_lock, &philo->flag, 1);
	pthread_mutex_unlock(philo->fork1_mutex);
	pthread_mutex_unlock(philo->fork2_mutex);
}

void	philo_think(t_philo *philo, int flag)
{
	long	time_to_sleep;
	long	time_to_eat;
	long	time_to_think;

	if (!flag)
		print_state(philo, THINKING);
	if (!(philo->data->nb_philo % 2))
		return ;
	time_to_sleep = philo->data->time_to_sleep;
	time_to_eat = philo->data->time_to_eat;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	ft_sleep(philo->data, time_to_think * 0.1);
}
