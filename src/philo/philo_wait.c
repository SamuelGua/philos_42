/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:22:17 by scely             #+#    #+#             */
/*   Updated: 2024/03/26 16:22:39 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_bool(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->info->ready);
	ret = philo->info->go;
	pthread_mutex_unlock(&philo->info->ready);
	return (ret);
}

void	wait_all_threads(t_philo *philo)
{
	while (get_bool(philo) == 0)
		usleep(500);
}

void	ft_usleep(int time_to, t_philo *philo)
{
	int	pourcent;

	pourcent = 0.1 * time_to;
	while(time_to > 0 && check_death(philo) == 0)
	{
		usleep(pourcent);
		time_to -= pourcent;
	}
}
