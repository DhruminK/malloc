/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:03:46 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/05 20:29:37 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	ft_str_frerror(void *addr)
{
	ft_putstr_fd("malloc: *** error for object ", 2);
	ft_puthex_fd((size_t)addr, 2, 1);
	ft_putstr_fd(": pointer being freed was not allocated", 2);
}

int	check_free_zone_alloc(void *addr)
{
	t_page_info	*pg_info;
	t_list		*alloc;
	int			b;

	pg_info = &(g_gen_info.tiny);
	b = 0;
	if (pg_info->page_start <= addr && pg_info->page_end > addr)
		b = 1;
	if (!b)
	{
		pg_info = &(g_gen_info.small);
		if (pg_info->page_start <= addr && pg_info->page_end > addr)
			b = 1;
	}
	if (!b)
		return (0);
	if (find_alloc_in_page(pg_info, addr, &alloc) < 1)
		return (-1);
	ft_zone_mem_dealloc(pg_info, alloc);
	return (1);
}

void	free(void *addr)
{
	int		b;
	t_list	*alloc;
	t_list	*pg;

	b = check_free_zone_alloc(addr);
	if (b == 0)
	{
		if (find_alloc_multi_page(g_gen_info.large, addr, &pg, &alloc) < 1)
			b = -1;
		if (b == 1 && ft_mem_dealloc(pg, alloc) == -1)
			b = -1;
	}
	if (b == -1)
		ft_str_frerror(addr);
}
