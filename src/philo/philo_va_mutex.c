
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