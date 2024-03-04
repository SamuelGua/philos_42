/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meca_971 <meca_971@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:44:47 by scely             #+#    #+#             */
/*   Updated: 2024/03/03 20:06:55 by meca_971         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


//656_843_591
//2_147_483_647
//-18446744073709551614 overflow long -2
void init_philo(char **av, t_philo **list)
{
	t_philo *tmp = *list;
	int num_philo = atoi(av[1]);
	int i = 0;
	while (i++ < num_philo)
	{
		tmp = ft_lstnew(i, av);
		if (!tmp)
			return;
		ft_lstadd_back(list, tmp);
	}
	tmp->next = *list;	
	(*list)->prev = tmp;
}
// nop = num_of_philo
void	*dinner(void *philo)
{
	t_philo *tmp = (t_philo *) philo;
	printf("id = %d\n", tmp->id);
	return NULL;
}
void printlist(t_philo *list, int num_of_philo)
{
	int j = 0;
	while (list && j++ < num_of_philo)
	{
		printf("philo->%i ", list->id);
		list = list->next;
	}
}
int	main(int ac, char **av)
{
	int	i;

	i = 1;
	t_philo *philo = NULL;
	t_philo  *tmp = NULL;
 	if (ac < 5 || ac > 6)
		return (printf("Wrongs arguments numbers\n"));
	while (av[i])
	{
		if (check_args(av[i], i) != 0)
			return (printf("Argument %d is incorrect\n", i));
		i++;
	}
	init_philo(av, &philo);
	tmp = philo;
	while (tmp->id != atoi(av[1]))
	{
		pthread_create(&tmp->thread, NULL, dinner, (void *) tmp);
		tmp = tmp->next;
	}
	tmp = philo;
	while (tmp->id != atoi(av[1]))
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
	printlist(philo, atoi(av[1]));
}
