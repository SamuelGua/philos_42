/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:05:04 by scely             #+#    #+#             */
/*   Updated: 2024/02/21 02:24:37 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*ft_lstnew(int content)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->content = content;
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
	}
	else
		*lst = new;
}
