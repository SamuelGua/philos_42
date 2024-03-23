/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:05:23 by scely             #+#    #+#             */
/*   Updated: 2024/03/23 16:50:03 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_message(t_philo *philo, char *str)
{
	int				temps;

	pthread_mutex_lock(&philo->info->print);
	if (philo->info->died == 1)
	{
		pthread_mutex_unlock(&philo->info->print);
		return ;
	}
	temps = get_time() - philo->info->begin;
	printf("%d %d %s\n", temps, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
}

void	take_forks(t_philo *philo)
{
	if (philo->info->died == 1)
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "\033[1;35mhas taken fork \033[0m");
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "\033[1;35mhas taken fork\033[0m");
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "\033[1;35mhas taken fork\033[0m");
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "\033[1;35mhas taken fork \033[0m");
	}
	philo->last_meals = get_time();
}

void	ft_eat(t_philo *philo)
{
	take_forks(philo);
	if (!check_end(philo) && philo->stats == 0)
	{
		ft_message(philo, "\033[0;32mis eating \033[0m");
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
	if (!check_end(philo) && philo->stats == 0)
	{
		ft_message(philo, "\033[0;34mis sleeping \033[0m");
		ft_usleep(philo->info->time_to_sleep, philo);
	}
	ft_message(philo, "\033[0;33mis thinking \033[0m");
}

void	ft_usleep(int time_to, t_philo *philo)
{
	int	pourcent;

	pourcent = time_to * 0.1;
	while (time_to > 0 && philo->info->died == 0)
	{
		usleep(pourcent);
		time_to -= pourcent;
	}
}
