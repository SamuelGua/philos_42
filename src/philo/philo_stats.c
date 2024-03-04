#include "philosophers.h"

void take_fork(int time, int philo)
{
    printf("%d %d has taken a fork", time, philo);
}

void ft_eating(int time, int philo)
{
    printf("%d %d is eating", time, philo);
}
void ft_thinking(int time, int philo)
{
    printf("%d %d is thinking", time, philo);
}
void ft_sleeping(int time, int philo)
{
    printf("%d %d is sleeping", time, philo);
}
void ft_death(int time, int philo)
{
    printf("%d %d died", time, philo);
}