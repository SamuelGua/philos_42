/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:44:47 by scely             #+#    #+#             */
/*   Updated: 2024/02/21 02:26:47 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


//656_843_591
//2_147_483_647
//-18446744073709551614 overflow long -2

int	main(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 6 || ac > 7)
		return (printf("Wrongs arguments numbers\n"));
	while (av[i])
	{
		if (check_args(av[i], i) != 0)
			return (printf("Argument %d is incorrect\n", i));
		i++;
	}
	
}
