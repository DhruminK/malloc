/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:12:40 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/13 12:14:49 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	main(void)
{
	int		i;
	char	*addr;

	i = -1;
	while (++i < 1024)
	{
		addr = malloc(1024);
		addr[0] = 42;
		free(addr);
	}
	return (0);
}