/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:26:31 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 18:30:31 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	gen_info_init(void)
{
	t_page_info	*pg_info;
	size_t		s;

	if (g_gen_info.is_alloc == 1)
		return (0);
	g_gen_info.pg_size = getpagesize();
	pg_info = &(g_gen_info.tiny);
	pg_info->page_start = (void *)TINY_ADDR;
	pg_info->page_end = (void *)SMALL_ADDR;
	pg_info->alloc_start = pg_info->page_start;
	pg_info->alloc = 0;
	s = (size_t)(SMALL_ADDR - TINY_ADDR);
	if (alloc_mmap((void *)TINY_ADDR, &s) == -1)
		return (-1);
	pg_info = &(g_gen_info.small);
	pg_info->page_start = (void *)SMALL_ADDR;
	pg_info->page_end = (void *)LARGE_ADDR;
	pg_info->alloc_start = pg_info->page_start;
	pg_info->alloc = 0;
	s = (size_t)(LARGE_ADDR - SMALL_ADDR);
	if (alloc_mmap((void *)SMALL_ADDR, &s) == -1)
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
		return (ft_zone_mem_alloc_start(pg_info, size));
	return (ft_zone_mem_alloc_mid(alloc, pg_info, size));
}

int	zone_dealloc(void *addr, t_page_info *pg_info)
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
		ft_lst_remove_front(&(pg_info->alloc));
	else
		ft_lst_remove_front(&(a->next));
	return (1);
}

void	*zone_realloc(void *addr, size_t size, int *ret)
{
	t_page_info	*pg_info[2];
	t_list		*alloc;
	int			i;

	pg_info[0] = &(g_gen_info.tiny);
	pg_info[1] = &(g_gen_info.small);
	i = -1;
	while (++i < 2)
	{
		if ((pg_info[i])->page_end > addr
			&& find_alloc_in_page(addr, pg_info[i], &alloc) == 0)
		{
			*ret = -1;
			return (0);
		}
		if ((pg_info[i])->page_end > addr)
			return (mem_alloc_zone(alloc, pg_info[i], size));
	}
	*ret = 0;
	return (0);
}

int	free_check_zones(void *addr)
{
	t_page_info	*pg_info[2];
	int			i;

	if (g_gen_info.is_alloc == 0)
		return (-1);
	i = -1;
	pg_info[0] = &(g_gen_info.tiny);
	pg_info[1] = &(g_gen_info.small);
	while (++i < 2)
	{
		if (pg_info[i] && ((pg_info[i])->page_end > addr))
		{
			if (zone_dealloc(addr, pg_info[i]) < 1)
				return (-1);
			return (1);
		}
	}
	return (0);
}
