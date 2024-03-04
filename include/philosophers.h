/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meca_971 <meca_971@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:45:17 by scely             #+#    #+#             */
/*   Updated: 2024/03/03 18:54:38 by meca_971         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>	  // memset
# include <stdio.h>	  // printf
# include <stdlib.h>	  // malloc, free
# include <unistd.h>	  // write, usleep, gettimeofday
# include <sys/time.h> // gettimeofday en fonction des systèmes
# include <pthread.h>  // les fonctions liées aux threads

typedef struct philosophers
{
	pthread_t		thread;
	int				id;

	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	unsigned int	time_to_death;
	unsigned int	minimun_of_meal;
	unsigned int	*is_dead;
	
	void			*prev;
	void			*next;
}	t_philo;

typedef struct t_list
{
	pthread_mutex_t mutex;
	t_philo **philos;
}	t_data;

// list init
t_philo	*ft_lstnew(int content, char **av);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);

// PARSING
int		ft_atoi(const char *c);
int		ft_isdigit(int c);
long	ft_atol(const char *c);
int		check_args(char *av, int j);

//print stats
void take_fork(int time, int philo);
void ft_eating(int time, int philo);
void ft_thinking(int time, int philo);
void ft_sleeping(int time, int philo);
void ft_death(int time, int philo);





void printlist(t_philo *list, int num_of_philo);
#endif
