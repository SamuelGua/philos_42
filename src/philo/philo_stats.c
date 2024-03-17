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

#include "philo.h"

void	ft_message(t_philo *philo, char *str, int time_to)
{
	int				temps;

	pthread_mutex_lock(&philo->info->print);
	if (philo->info->died == 1)
	{
		pthread_mutex_unlock(&philo->info->print);
		return;
	}
	ft_died(philo, time_to);
	temps = get_time() - philo->info->begin;
	if (philo->stats == 1)
		printf("%d %d %s\n", temps, philo->id, "is dead");
	else
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

	ft_message(philo, "is eating", philo->info->time_to_eat);
	philo->last_meals = get_time();
	usleep(philo->info->time_to_eat);
	philo->n_meals++;
	pthread_mutex_lock(&philo->info->meal);
	if (philo->n_meals == philo->info->num_of_eat)
		philo->info->all_eataen++;
	pthread_mutex_unlock(&philo->info->meal);
	//printf("philo = %d | n_meals = %d | ", philo->id, philo->n_meals);
	//printf("*_meals = %d\n", philo->info->all_eataen);
	pthread_mutex_unlock(&philo->fork_id);
	pthread_mutex_unlock(&philo->prev->fork_id);
}

void	ft_sleep(t_philo *philo)
{
	ft_message(philo, "is sleeping", philo->info->time_to_sleep);
	usleep(philo->info->time_to_sleep);
	ft_message(philo, "is thinking", 0);
}

void	ft_died(t_philo *philo, int time_to)
{
	int				temps;

	temps = (get_time() - philo->last_meals);
	if (philo->info->time_to_death / 1000 > temps + (time_to / 1000))
		return ;
	else
	{
		philo->info->died = 1;
		philo->stats = 1;
		usleep((philo->info->time_to_death / 1000 - temps) * 1000);
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