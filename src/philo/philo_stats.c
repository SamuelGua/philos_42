/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:05:23 by scely             #+#    #+#             */
/*   Updated: 2024/03/07 12:06:32 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_message(t_philo *philo, char *str)
{
	int				temps;

	temps = get_time() - philo->info->begin;
	pthread_mutex_lock(&philo->info->print);
	printf("%d %d %s\n", temps, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		ft_died(philo);
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "has taken fork");
		ft_died(philo);
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "has taken fork");
	}
	else
	{
		ft_died(philo);
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "has taken fork");
		ft_died(philo);
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "has taken fork");
	}
	ft_died(philo);
	ft_message(philo, "is eating");
	usleep(philo->info->time_to_eat);
	philo->last_meals = get_time();
	pthread_mutex_unlock(&philo->fork_id);
	pthread_mutex_unlock(&philo->prev->fork_id);
}

void	ft_sleep(t_philo *philo)
{
	ft_message(philo, "is sleeping");
	usleep(philo->info->time_to_sleep);
	ft_message(philo, "is thinking");
}

void	ft_died(t_philo * philo)
{
	int				temps;

	temps = get_time() - philo->last_meals;
	if (temps <= philo->info->time_to_death / 1000)
		return ;
	ft_message(philo, "is dead 😈");
}

double get_time()
{
	struct timeval	time;
	double			abs_time;

	gettimeofday(&time, NULL);
	abs_time = (time.tv_sec + ((double)time.tv_usec / 1000000)) * 1000;
	return (abs_time);
}