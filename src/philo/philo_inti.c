/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:35:07 by scely             #+#    #+#             */
/*   Updated: 2024/03/21 13:54:39 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(char **av, t_philo **list, t_data *data)
{
	t_philo	*tmp;
	int		num_philo;
	int		i;

	tmp = *list;
	num_philo = atoi(av[1]);
	i = 0;
	while (i++ < num_philo)
	{
		tmp = ft_lstnew(i);
		if (!tmp)
			return ;
		tmp->info = data;
		ft_lstadd_back(list, tmp);
	}
	tmp->next = *list;
	(*list)->prev = tmp;
}

void	init_mutex(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = data->philos;
	while (i++ < data->num_of_philo)
	{
		pthread_mutex_init(&data->philos->fork_id, NULL);
		pthread_mutex_init(&data->philos->last_meals_mutex, NULL);
		data->philos = data->philos->next;
	}
	data->philos = tmp;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->died_mutex, NULL);
}

void	init_destroy_mutex(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = data->philos;
	while (i++ < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->philos->fork_id);
		data->philos = data->philos->next;
	}
	data->philos = tmp;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal);
}

void	init_data(char **av, t_data *data)
{
	data->philos = NULL;
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_death = ft_atoi(av[2]) * 1000;
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	data->died = 0;
	data->all_eataen = 0;
	if (av[5] == NULL || ft_atoi(av[5]) == 0)
		data->num_of_eat = -1;
	else
		data->num_of_eat = ft_atoi(av[5]);
	init_philo(av, &data->philos, data);
	init_mutex(data);
}

double	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
