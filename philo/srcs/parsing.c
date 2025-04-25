/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:54:42 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/20 20:54:43 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int     parsing(t_data *data, char **av)
{
        if (args_check(av))
                return (1);
        if (args_check2(av))
                return (1);
        data->nb_philo = ft_atol(av[1]);
        data->time_to_die = ft_atol(av[2]) * 1000;
        data->time_to_eat = ft_ato(av[3]) * 1000;
        data->time_to_sleep = ft_atol(av[4]) * 1000;
        if (av[5])
        {
                data->max_meals = ft_atol(av[5]);
                if (data->max_meals < 0)
                {
                        printf("Error : All arguments must be only posetive numbers :(\n");
                        return (1);
                }
        }
        if (num_check(data))
                return (1);
        return (0);

}

int	args_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isalpha(av[i][j]))
			{
				printf("Error : Argument %d has invalid input\n", i);
				return (1);
			}
			j++;
		}
	}
}

int     args_check2(char **av)
{
        int     i;
        int     j;

        i = 0;
        while (av[i])
        {
                j = 0;
                if (av[i][j] == '-' || av[i][j] == '+')
                        j++;
                while ((av[i][j] >= 48 && av[i][j] <= 57) && av[i][j])
                        j++;
                while (av[i][j])
                {
                        if (av[i][j] == '+' || av[i][j] == '-')
                        {
                                printf("Error : Argument %d has invalid input\n"i);
                                return (1);
                        }
                        j++;
                }
                i++;
        }
        return (0);
}

int	num_check(t_data *data)
{
	if (data->nb_philo > 200)
	{
		printf("Error : Number of philos must be less that 200 :(\n");
		return (1);
	}
	if (data -> nb_philos <= 0 || data->time_to_die <= 0 || data->time_to_sleep <= 0 || data->time_to_eat <= 0)
	{
		printf("Error : All arguments must be only positive numbers :(\n");
		return (1);
	}
	return (0);
}
