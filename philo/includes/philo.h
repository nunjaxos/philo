#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>

typedef enum	e_state
{
	FORK1,
	FORK2,
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}		t_state;

typedef struct	s_philo
{
	int	meals_count;
	int	pos;
	int	flag;
	long	last_meal;
	t_data	*data;
	pthread_t	thread;
	pthread_mutex_t	*fork1_mutex;
	pthread_mutex_t	*fork2_mutex;
	pthread_mutex_t	state_lock;
}		t_philo;

typedef struct	s_data
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	long	max_meals;
	t_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	data_lock;
}		t_data;

		//parisng
int     parsing(t_data *data, char **av);
int     args_check(char **av);
int     args_check2(char **av);
int     num_check(t_data *data);
		//utils
int     is_alpha(char c);
static long     atol_norm(const char *str, size_t r, long s, long *i);
long    ft_atol(const char *str);

#endif
