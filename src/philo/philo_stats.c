/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:05:23 by scely             #+#    #+#             */
/*   Updated: 2024/03/21 16:54:01 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*=======================================================*/

int	get_bool(t_data *data)
{
	int	ret;

	usleep(200);
	pthread_mutex_lock(&data->synchro);
	ret = data->ready;
	pthread_mutex_unlock(&data->synchro);
	return (ret);
}
void	wait_all_threads(t_data *table)
{	
	while (!get_bool(table))
		;
}
/*=======================================================*/

void	ft_message(t_philo *philo, char *str, int time_to)
{
	int				temps;

	pthread_mutex_lock(&philo->info->print);
	if (philo->info->died == 1)
	{
		pthread_mutex_unlock(&philo->info->print);
		return;
	}
	(void)time_to;
	//ft_died(philo, time_to);
	temps = get_time() - philo->info->begin;
	if (philo->stats == 1)
	{
		printf("%d %d %s\n", temps, philo->id, "\033[1;31m is dead\033[0m");
	}
	else
		printf("%d %d %s\n", temps, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
}

void	ft_eat(t_philo *philo)
{
	if (philo->n_meals < 2 )
		printf("last meals %f\n", (get_time() - philo->last_meals));
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "\033[1;35m has taken fork \033[0m", 0);
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "\033[1;35m has taken fork - 1 \033[0m",0);
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork_id);
		ft_message(philo, "\033[1;35m has taken fork - 1 \033[0m", 0);
		pthread_mutex_lock(&philo->fork_id);
		ft_message(philo, "\033[1;35m has taken fork \033[0m", 0);
	}
	philo->last_meals = get_time();
	ft_message(philo, "\033[0;32m is eating \033[0m", philo->info->time_to_eat);
	if (philo->stats == 1)
	{
		pthread_mutex_unlock(&philo->fork_id);
		pthread_mutex_unlock(&philo->prev->fork_id);
		return ;
	}
	ft_usleep(philo->info->time_to_eat);
	philo->n_meals++;
	pthread_mutex_lock(&philo->info->meal);
	if (philo->n_meals == philo->info->num_of_eat)
		philo->info->all_eataen++;
	pthread_mutex_unlock(&philo->info->meal);
	pthread_mutex_unlock(&philo->fork_id);
	pthread_mutex_unlock(&philo->prev->fork_id);
}

void	ft_sleep(t_philo *philo)
{
	ft_message(philo, "\033[0;34m is sleeping \033[0m", philo->info->time_to_sleep);
	ft_usleep(philo->info->time_to_sleep);
	ft_message(philo, "\033[0;33m is thinking \033[0m",0);
}

void	ft_died(t_philo *philo, int time_to)
{
	int				temps;
	//(void)time_to;

	temps = (get_time() - philo->last_meals);
	printf("{%d} ", philo->id);
	printf("temps = %d || time-to = %d || death = %d\n", temps, time_to / 1000, philo->info->time_to_death / 1000);
	// if ((philo->info->time_to_death / 1000) >= (temps/* + (time_to / 1000)*/))
	//  	return ;
	if ((temps + time_to / 1000 > (philo->info->time_to_death / 1000) + 5) || (time_to > philo->info->time_to_death) )
	{
		printf("temps + action = %d || death = %d\n", temps + time_to / 1000, philo->info->time_to_death / 1000);

		philo->info->died = 1;
		philo->stats = 1;
		ft_usleep(( philo->info->time_to_death  / 1000 - temps) * 1000);
		return;
	}
	
}

void	ft_usleep(int time_to)
{
	int pourcent = time_to * 0.1;

	while (time_to > 0)
	{
		usleep(pourcent);
		time_to -= pourcent;
	}
}

