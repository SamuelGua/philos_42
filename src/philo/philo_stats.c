/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:05:23 by scely             #+#    #+#             */
/*   Updated: 2024/03/16 13:46:32 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_message(t_philo *philo, char *str, int time_to)
{
	int				temps;

	temps = get_time() - philo->info->begin;
	ft_died(philo, time_to);
	if(philo->info->died == 1 && philo->stats == 1)
	{
		philo->stats--;
		pthread_mutex_lock(&philo->info->print);
		printf("%d %d %s\n", temps, philo->id, "is dead");
		pthread_mutex_unlock(&philo->info->print);
		return;
	}
	else if (philo->info->died == 1)
		return;
	pthread_mutex_lock(&philo->info->print);
	printf("%d %d %s\n", temps, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_t test;
	pthread_mutex_init(&test, NULL);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "has taken fork", philo->info->time_to_eat);
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "has taken fork", philo->info->time_to_eat);
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "has taken fork", philo->info->time_to_eat);
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "has taken fork", philo->info->time_to_eat);
	}
	philo->last_meals = get_time();
	ft_message(philo, "has taken fork", philo->info->time_to_eat);
	philo->n_meals++;
	if (philo->n_meals == philo->info->num_of_eat)
	{
		pthread_mutex_lock(&test);
		philo->info->all_eataen += 1;
		pthread_mutex_unlock(&test);
	}
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->fork_id);
	pthread_mutex_unlock(&philo->prev->fork_id);
}

void	ft_sleep(t_philo *philo)
{
	ft_message(philo, "has taken fork", philo->info->time_to_sleep);
	usleep(philo->info->time_to_sleep);
	ft_message(philo, "is thinking", 0);
}

void	ft_died(t_philo *philo, int time_to)
{
	int				temps;

	temps = ((get_time() - philo->last_meals)) + (time_to / 1000);

	if (philo->info->time_to_death / 1000 > temps)
		return ;
	else if (philo->info->time_to_death / 1000 < temps)
	{
		philo->info->died = 1;
		philo->stats = 1;
		if (philo->info->time_to_death / 1000 > (get_time() - philo->last_meals))
			usleep((philo->info->time_to_death / 1000 - ((get_time() - philo->last_meals))) * 1000);
	}
}

double get_time()
{
	struct timeval	time;
	double			abs_time;

	gettimeofday(&time, NULL);
	abs_time = (time.tv_sec + ((double)time.tv_usec / 1000000)) * 1000;
	return (abs_time);
}