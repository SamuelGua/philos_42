/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:45:17 by scely             #+#    #+#             */
/*   Updated: 2024/03/21 12:38:30 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>	// memset
# include <stdio.h>	  	// printf
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write, usleep, gettimeofday
# include <sys/time.h>	// gettimeofday en fonction des systèmes
# include <pthread.h> 	// les fonctions liées aux threads

struct	s_list;

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
	struct s_list			*info;
}	t_philo;

typedef struct s_list
{
	pthread_mutex_t	print;
	pthread_mutex_t	meal;

	pthread_mutex_t	synchro;
	pthread_t		monitor;
	int				ready;

	int				num_of_philo;
	t_philo			*philos;

	int				died;
	int				all_eataen;

	int				time_to_death;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;	

	double			begin;
}	t_data;

// list utils
t_philo	*ft_lstnew(int content);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
void	ft_free(t_philo *lst, int num_philo);
void	printlist(t_philo *list, int num_of_philo);

// parsing
int		ft_atoi(const char *c);
int		ft_isdigit(int c);
long	ft_atol(const char *c);
int		check_args(char *av, int j);

// inti data
void	init_data(char **av, t_data *data);
void	init_mutex(t_data *data);
void	init_destroy_mutex(t_data *data);
void	init_philo(char **av, t_philo **list, t_data *data);
double	get_time(void);

/*==============*/
void	wait_all_threads(t_data *table);
int		get_bool(t_data *data);
/*==============*/

// philo manager
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_died(t_philo *philo, int time_to);
void	ft_message(t_philo *philo, char *str, int time_to);
void	ft_usleep(int time_to);

#endif
