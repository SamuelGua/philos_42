/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:18:41 by scely             #+#    #+#             */
/*   Updated: 2024/03/19 14:51:32 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *c)
{
	int	i;
	int	res;
	int	minus;

	i = 0;
	res = 0;
	minus = 1;
	while (c[i] == 32 || (c[i] >= 9 && c[i] <= 13))
		i++;
	if (c[i] == 45)
	{
		i++;
		minus = -1;
	}
	else if (c[i] == 43)
		i++;
	while (c[i] >= 48 && c[i] <= 57)
	{
		res = 10 * res + (c[i] - '0');
		i++;
	}
	return (res * minus);
}

long	ft_atol(const char *c)
{
	long	i;
	long	res;
	long	minus;

	i = 0;
	res = 0;
	minus = 1;
	while (c[i] == 32 || (c[i] >= 9 && c[i] <= 13))
		i++;
	if (c[i] == 45)
	{
		i++;
		minus = -1;
	}
	else if (c[i] == 43)
		i++;
	while (c[i] >= 48 && c[i] <= 57)
	{
		res = 10 * res + (c[i] - '0');
		i++;
	}
	return (res * minus);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	check_args(char *av, int j)
{
	int	i;

	i = 0;
	if (av[i] == '-')
		return (1);
	else if (av[i] == '+')
		i++;
	while (av[i])
	{
		if (ft_isdigit(av[i]) == 0 || i > 10)
			return (1);
		i++;
	}
	if (j == 6 && (ft_atol(av) < 0 || ft_atol(av) >= __INT_MAX__))
		return (1);
	else if (j != 6 && (ft_atol(av) < 1 || ft_atol(av) >= __INT_MAX__))
		return (1);
	return (0);
}

void	printlist(t_philo *list, int num_of_philo)
{
	int	j;

	j = 0;
	while (j++ < num_of_philo)
	{
		printf("philo->%i prev <-%d | ", list->id, list->prev->id);
		list = list->next;
	}
}