/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:44:47 by scely             #+#    #+#             */
/*   Updated: 2024/03/19 14:47:01 by scely            ###   ########.fr       */
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
		tmp->n_meals = 0;
		tmp->stats = 0;
		tmp->last_meals = 0;
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
		data->philos = data->philos->next;
	}
	data->philos = tmp;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
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

int check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print);
	if (philo->info->died == 1)
		return (pthread_mutex_unlock(&philo->info->print), 1);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(&philo->info->meal);
	if (philo->info->all_eataen == philo->info->num_of_philo)
		return (pthread_mutex_unlock(&philo->info->meal), 1);
	pthread_mutex_unlock(&philo->info->meal);
	return (0);
}

void	*dinner(void *philo)
{
	t_philo	*tmp;
	tmp = (t_philo *) philo;
	if (tmp->info->num_of_philo == 1)
	{
		usleep(tmp->info->time_to_death);
		printf("%d %d %s\n", (int)(get_time() - tmp->info->begin), tmp->id, "is dead");
		return (NULL);
	}
	tmp->last_meals = tmp->info->begin;
	while (!check_end(philo))
	{
		ft_eat(tmp);
		ft_sleep(tmp);
	}
	return (NULL);
}

void	thread(t_data *data)
{
	int				i;

	data->begin = get_time();
	i = 0;
	while (i++ < data->num_of_philo)
	{
		pthread_create(&data->philos->thread, NULL, &dinner, data->philos);
		data->philos = data->philos->next;
	}

	while (--i > 0)
	{
		pthread_join(data->philos->thread, NULL);
		data->philos = data->philos->next;
	}
}

int	main(int ac, char **av)
{
	int		i;
	t_data	data;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("Wrongs arguments numbers\n"));
	while (av[i])
	{
		if (check_args(av[i], i) != 0)
			return (printf("Argument %d is incorrect\n", i));
		i++;
	}
	init_data(av, &data);
	thread(&data);
	printlist(data.philos, data.num_of_philo);
	ft_free(data.philos, data.num_of_philo);
}
