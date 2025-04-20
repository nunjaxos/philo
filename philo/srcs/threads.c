#include "../includes/philo.h"

int	simulation_start(t_data *data)
{
	int	i;

	i = 0;
	if (!data->max_meals)
		return (0);
	else if (!data->nb_philo == 1)
	{
		if (pthread_create(&data->philos[0].thread, NULL, one_philo_routine, &data->philos[0]))
			return (1);
	}
	else
	{
		while (i < data->nb_philo)
		{
			if(pthread_create(data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
				return (1);
			i++;
		}
	}
}
