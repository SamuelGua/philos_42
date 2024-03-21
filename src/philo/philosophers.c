/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:44:47 by scely             #+#    #+#             */
/*   Updated: 2024/03/21 13:59:28 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_philo *philo)
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
void	*manage(void *tmp)
{
	t_data *data;

	data = (t_data *) tmp;
	while (1)
	{
		if ((get_time() - data->philos->last_meals) > data->time_to_death + 5)
		{
			printf("temps = %f | last-meal %f | ttd = %d\n", get_time(), data->philos->last_meals, data->time_to_death);
			printf("last-meal %f | ttd = %d\n",(get_time() - data->philos->last_meals), data->time_to_death);
			data->died = 1;
			data->philos->stats = 1;
			exit(1);
		}
		data->philos = data->philos->next;
	}
}

void	*dinner(void *philo)
{

	t_philo	*tmp;

	tmp = (t_philo *) philo;
	//tmp->last_meals = get_time();
	//printf("[%d] dinner last-meals = %f\n",tmp->id, tmp->last_meals);
	//pthread_create(&tmp->info->monitor, NULL, &manage, tmp->info);
	//pthread_detach(tmp->info->monitor);
	if (tmp->info->num_of_philo == 1)
	{
		printf("%d %d %s\n", (int)(get_time()
				- tmp->info->begin), tmp->id, "has taken a fork");
		ft_usleep(tmp->info->time_to_death);
		printf("%d %d %s\n", (int)(get_time()
				- tmp->info->begin), tmp->id, "is dead");
		return (NULL);
	}
	pthread_mutex_init(&tmp->info->synchro, NULL);
	tmp->last_meals = tmp->info->begin;
	ft_message(philo, "\033[0;33m is thinking \033[0m", 0);
	while (!check_end(tmp))
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
	data->ready = 0;
	pthread_mutex_init(&data->synchro, NULL);
	while (i++ < data->num_of_philo)
	{
		if (i == data->num_of_philo)
			data->ready = 1;
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
