/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:54:59 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/27 18:51:42 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef enum e_state
{
	FORK1,
	FORK2,
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}						t_state;

typedef struct s_philo
{
	int					meals_count;
	int					pos;
	int					flag;
	long				last_meal;
	t_data				*data;
	pthread_t			thread;
	pthread_mutex_t		*fork1_mutex;
	pthread_mutex_t		*fork2_mutex;
	pthread_mutex_t		state_lock;
}						t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long				max_meals;
	int					simulation_end;
	int					thread_flag;
	long				thread_active;
	long				start_time;
	t_philo				*philos;
	pthread_t			monitoring;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		data_lock;
}						t_data;

// routine functions
void					*one_philo_routine(void *arg);
void					*philo_routine(void *arg);
void					*monitoring(void *arg);

// time functions
void					ft_sleep(t_data *data, unsigned long sleep_time);
long					get_time(void);

// init function
int						init(t_data *data);

// utils functions
void					update_value(pthread_mutex_t *mutex, int *update,
							int value);
void					increment_value(pthread_mutex_t *mutex, long *value);
long					get_safe_value(pthread_mutex_t *mutex, long *value);
int						get_safe_flag(pthread_mutex_t *mutex, int *flag);
int						simulation_end(t_data *data);
int						thread_active(pthread_mutex_t *mutex, long *value,
							long nb_philo);
void					update_long_value(pthread_mutex_t *mutex, long *update,
							long value);

// threads functions
void					print_state(t_philo *philo, t_state state);
void					philo_think(t_philo *philo, int flag);
void					philo_eat(t_philo *philo);
int						simulation_start(t_data *data);
int						exiting(t_data *data);
int						simulation_start(t_data *data);

// parsing functions
int						param_parse(t_data *data, char **av);
int						args_check(char **av);
int						num_check(t_data *data);
void					cleanup(t_data *data);
long					ft_atol(const char *str);
int						ft_isalpha(int c);
int						another_check(char **av);

#endif