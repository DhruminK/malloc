/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:53:41 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 14:14:27 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	zone_alloc_init(void)
{
	size_t	pg_size;

	pg_size = (size_t)(getpagesize());
	g_gen_info.pg_size = pg_size;
	if (g_gen_info.is_tiny_alloc && g_gen_info.is_small_alloc)
		return (1);
	if (!(g_gen_info.is_tiny_alloc)
		&& new_zone_alloc(&(g_gen_info.tiny), TZ_SIZE * pg_size) == -1)
		return (-1);
	g_gen_info.is_tiny_alloc = 1;
	if (!(g_gen_info.is_small_alloc)
		&& new_zone_alloc(&(g_gen_info.small), SZ_SIZE * pg_size) == -1)
		return (-1);
	g_gen_info.is_small_alloc = 1;
	return (1);
}

void	*mem_alloc_init(t_page_info *pg_info, t_list *prev, size_t size)
{
	t_list	*ele;

	if (!pg_info)
		return (0);
	if (prev)
		ele = (t_list *)((size_t)(prev->content) + prev->size);
	else if (!prev && pg_info->alloc)
		ele = (t_list *)(pg_info->alloc - size - sizeof(t_list));
	else
		ele = (t_list *)(pg_info->alloc_start);
	ele->content = (void *)((size_t)ele + sizeof(t_list));
	ele->size = size;
	if (!prev)
		ft_lst_add_front((t_list **)(&(pg_info->alloc)), ele);
	else
		ft_lst_add_front(&(prev->next), ele);
	return (ele->content);
}

void	*zone_mem_alloc(size_t size, t_page_info *pg_info)
{
	t_list	*prev;

	prev = 0;
	if (find_size_in_pg(pg_info, size, &prev) < 1)
		return (0);
	return (mem_alloc_init(pg_info, prev, size));
}

void	*mem_alloc(size_t size)
{
	t_list	*prev;
	t_list	*pg;
	int		ret;

	prev = 0;
	pg = 0;
	ret = find_size(g_gen_info.large, size, &pg, &prev);
	if (ret == 1 && pg)
		return (mem_alloc_init((t_page_info *)(pg->content), prev, size));
	pg = 0;
	if (new_page_alloc(&(g_gen_info.large),
			size + sizeof(t_list), &pg) == -1 || !pg)
		return (0);
	return (zone_mem_alloc(size, (t_page_info *)(pg->content)));
}
