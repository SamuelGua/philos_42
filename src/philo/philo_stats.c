/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:05:23 by scely             #+#    #+#             */
/*   Updated: 2024/03/28 13:47:48 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(t_philo *philo, char *str)
{
	int				temps;

	pthread_mutex_lock(&philo->info->print);
	if (mutex_died(philo))
	{
		pthread_mutex_unlock(&philo->info->print);
		return ;
	}
	temps = get_time() - mutex_begin(philo);
	printf("%d %d %s\n", temps, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "\033[1;35mhas taken a fork\033[0m");
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "\033[1;35mhas taken a fork\033[0m");
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "\033[1;35mhas taken a fork\033[0m");
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "\033[1;35mhas taken a fork\033[0m");
	}
	pthread_mutex_lock(&philo->last_meals_mutex);
	philo->last_meals = get_time();
	pthread_mutex_unlock(&philo->last_meals_mutex);
}

void	ft_eat(t_philo *philo)
{
	take_forks(philo);
	if (!check_end(philo))
	{
		ft_message(philo, "\033[0;32mis eating\033[0m");
		ft_usleep(philo->info->time_to_eat, philo);
		philo->n_meals++;
		pthread_mutex_lock(&philo->info->meal);
		if (philo->n_meals == philo->info->num_of_eat)
			philo->info->all_eataen++;
		pthread_mutex_unlock(&philo->info->meal);
	}
	pthread_mutex_unlock(&philo->fork_id);
	pthread_mutex_unlock(&philo->prev->fork_id);
}

void	ft_sleep(t_philo *philo)
{
	if (!check_end(philo))
	{
		ft_message(philo, "\033[0;34mis sleeping\033[0m");
		ft_usleep(philo->info->time_to_sleep, philo);
	}
	ft_message(philo, "\033[0;33mis thinking\033[0m");
	ft_usleep(philo->info->time_to_think, philo);
}
