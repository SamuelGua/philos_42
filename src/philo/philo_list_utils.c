/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:05:04 by scely             #+#    #+#             */
/*   Updated: 2024/03/07 12:08:21 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int content)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = content;
	new->n_meals = 0;
	new->last_meals = get_time();
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

void	ft_free(t_philo *lst, int num_philo)
{
	t_philo	*tmp;

	while (num_philo--)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	printlist(t_philo *list, int num_of_philo)
{
	int	j;

	j = 0;
	while (j++ < num_of_philo)
	{
		printf("philo->%i prev <-%d | ", list->id, list->prev->id);
		list = list->next;
	}
	printf("\n");
}
