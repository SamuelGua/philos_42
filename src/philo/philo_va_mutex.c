/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_va_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:27:37 by scely             #+#    #+#             */
/*   Updated: 2024/03/28 13:49:09 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_philo *philo)
{
	if (mutex_meal(philo) || mutex_died(philo))
		return (1);
	return (0);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meals_mutex);
	if ((get_time() - philo->last_meals)
		> philo->info->time_to_death / 1000)
		return (pthread_mutex_unlock(&philo->last_meals_mutex), 1);
	return (pthread_mutex_unlock(&philo->last_meals_mutex), 0);
}

int	mutex_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->meal);
	if (philo->info->all_eataen == philo->info->num_of_philo)
		return (pthread_mutex_unlock(&philo->info->meal), 1);
	return (pthread_mutex_unlock(&philo->info->meal), 0);
}

int	mutex_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->died_mutex);
	if (philo->info->died == 1)
		return (pthread_mutex_unlock(&philo->info->died_mutex), 1);
	return (pthread_mutex_unlock(&philo->info->died_mutex), 0);
}

double	mutex_begin(t_philo *philo)
{
	double	tmp;

	pthread_mutex_lock(&philo->info->mutex_begin);
	tmp = philo->info->begin;
	pthread_mutex_unlock(&philo->info->mutex_begin);
	return (tmp);
}
