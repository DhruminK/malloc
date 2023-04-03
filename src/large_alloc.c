/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:40:23 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 17:47:08 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*large_alloc(size_t size)
{
	t_list	*alloc;
	t_list	*pg;

	pg = 0;
	alloc = 0;
	if (find_size(size, &pg, &alloc) == -1)
		return (0);
	if (!alloc)
		return (ft_mem_alloc_start(pg, size));
	return (ft_mem_alloc_mid(alloc, pg, size));
}

int	large_dealloc(void *addr)
{
	t_list	*pg;
	t_list	*alloc;

	pg = 0;
	alloc = 0;
	if (find_alloc(addr, &pg, &alloc) == -1)
		return (-1);
	return (ft_mem_dealloc(alloc, pg));
}

void	*large_realloc(void *addr, size_t size, int *ret)
{
	t_list	*pg;
	t_list	*alloc;

	pg = 0;
	alloc = 0;
	*ret = -1;
	if (find_alloc(addr, &pg, &alloc) == -1)
		return (0);
	*ret = 0;
	return (mem_realloc(alloc, pg, size));
}
