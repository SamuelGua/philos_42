/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meca_971 <meca_971@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:05:04 by scely             #+#    #+#             */
/*   Updated: 2024/03/03 16:59:47 by meca_971         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*ft_lstnew(int content , char **av)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->time_to_eat = atoi(av[3]);
	new->time_to_sleep = atoi(av[4]);
	new->time_to_death = atoi(av[2]);
	new->minimun_of_meal = 0;
	new->id = content;
	new->next = NULL;
	return (new);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*liste;

	if (*lst)
	{
		liste = ft_lstlast(*lst);
		liste->next = new;
		new->prev = liste;
	}
	else
		*lst = new;
}
