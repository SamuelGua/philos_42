/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:44:47 by scely             #+#    #+#             */
/*   Updated: 2024/03/23 16:41:21 by scely            ###   ########.fr       */
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
	if((get_time() - philo->last_meals)
			- 7 > philo->info->time_to_death / 1000)
		return (pthread_mutex_unlock(&philo->last_meals_mutex), 1);
	return (pthread_mutex_unlock(&philo->last_meals_mutex), 0);

}

int mutex_meal(t_philo *philo)
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

void	*manage(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while (1)
	{
		if (check_death(philo))
		{
			pthread_mutex_lock(&philo->info->died_mutex);
			philo->info->died = 1;
			pthread_mutex_unlock(&philo->info->died_mutex);
			pthread_mutex_lock(&philo->info->print);
			printf("[%d] last meals %f\n", philo->id, (get_time() - philo->last_meals));
			printf("%d %d \033[0;31mdied\033[0m\n",
				(int)(get_time() - philo->info->begin), philo->id);
			pthread_mutex_unlock(&philo->info->print);
			return (NULL);
		}
		if (mutex_meal(philo))
		{
			pthread_mutex_lock(&philo->info->died_mutex);
			philo->info->died = 1;
			pthread_mutex_unlock(&philo->info->died_mutex);
			return (NULL);
		}
		philo = philo->next;
		usleep(500);
	}
}

void	*dinner(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *) philo;
	if (tmp->info->num_of_philo == 1)
	{
		printf("%d %d %s\n", (int)(get_time()
				- tmp->info->begin), tmp->id, "has taken a fork");
		ft_usleep(tmp->info->time_to_death, tmp);
		printf("%d %d %s\n", (int)(get_time()
				- tmp->info->begin), tmp->id, "died");
		return (NULL);
	}
	ft_message(philo, "\033[0;33mis thinking \033[0m");
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
	if (data->num_of_philo != 1)
	{
		pthread_create(&data->monitor, NULL, &manage, data->philos);
		pthread_detach(data->monitor);
	}
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
	ft_free(data.philos, data.num_of_philo);
	return (0);
}
