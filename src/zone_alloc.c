/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:26:31 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/01 16:48:10 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	gen_info_init(void)
{
	t_page_info	*pg_info;

	if (g_gen_info.is_alloc == 1)
		return (0);
	g_gen_info.pg_size = getpagesize();
	pg_info = &(g_gen_info.tiny);
	pg_info->page_start = TINY_ADDR;
	pg_info->page_end = SMALL_ADDR;
	pg_info->alloc_start = pg_info->page_start;
	pg_info->alloc = 0;
	if (alloc_mmap(TINY_ADDR, (size_t)(SMALL_ADDR - TINY_ADDR)) == -1)
		return (-1);
	pg_info = &(g_gen_info.small);
	pg_info->page_start = SMALL_ADDR;
	pg_info->page_end = LARGE_ADDR;
	pg_info->alloc_start = pg_info->page_start;
	pg_info->alloc = 0;
	if (alloc_mmap(SMALL_ADDR, (size_t)(LARGE_ADDR - SMALL_ADDR)) == -1)
		return (-1);
	g_gen_info.is_alloc = 1;
	return (0);
}

void	*zone_alloc(size_t size, t_page_info *pg_info)
{
	t_list	*alloc;

	alloc = 0;
	if (find_size_page(size, pg_info, &alloc) == 0)
		return (0);
	if (!alloc)
		return (ft_mem_alloc_start(pg_info, size));
	return (ft_mem_alloc_mid(alloc, pg_info, size));
}

int		zone_dealloc(void *addr, t_page_info *pg_info)
{
	t_list	*alloc;
	t_list	*a;
	int		ret;

	if (!pg_info)
		return (0);
	ret = 0;
	ret = find_alloc_in_page(addr, pg_info, &alloc);
	if (ret < 1 || !alloc)
		return (ret);
	a = pg_info->alloc;
	while (a != alloc && a->next != alloc)
		a = a->next;
	if (a == alloc)
		ft_lst_remove_front(&(pg->alloc));
	else
		ft_lst_remove_front(&(a->next));
	return (1);
}
