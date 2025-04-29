/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:54:54 by abhmidat          #+#    #+#             */
/*   Updated: 2025/04/27 18:53:08 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}

int	another_check(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
		while ((av[i][j] >= '0' && av[i][j] <= '9') && av[i][j])
			j++;
		while (av[i][j])
		{
			if (av[i][j] == '+' || av[i][j] == '-')
			{
				printf("Error: Argument %d has invalid input\n", i);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
