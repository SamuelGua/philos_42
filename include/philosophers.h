/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:45:17 by scely             #+#    #+#             */
/*   Updated: 2024/03/16 13:01:46 by scely            ###   ########.fr       */
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

struct t_list;

typedef struct philosophers
{
	int						id;

	pthread_t				thread;
	pthread_mutex_t			fork_id;

	int						n_meals;
	double					last_meals;

	int						stats;
	struct philosophers		*prev;
	struct philosophers		*next;
	struct t_list			*info;
}	t_philo;

typedef struct t_list
{
	pthread_mutex_t print;
	pthread_mutex_t meal;
	
	int			num_of_philo;
	t_philo		*philos;
	int			died;
	int 		all_eataen;

	int			num_of_eat;	
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_death;
	double		begin;		

}	t_data;

// list init
t_philo	*ft_lstnew(int content);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);

// PARSING
int		ft_atoi(const char *c);
int		ft_isdigit(int c);
long	ft_atol(const char *c);
int		check_args(char *av, int j);

//print stats
void	ft_message(t_philo *philo, char *str, int time_to);
void 	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_died(t_philo * philo, int time_to);

void 	ft_free(t_philo *lst, int num_philo);
void	init_destroy_mutex(t_data *data);
double 	get_time();

void printlist(t_philo *list, int num_of_philo);
#endif
