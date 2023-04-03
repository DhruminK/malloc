/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:56:32 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 17:34:28 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	find_realloc_same_ele_pg(t_list *alloc, t_page_info *pg_info, size_t size)
{
	if (!alloc || !pg_info)
		return (0);
	if ((alloc->next) && (size_t)((void *)alloc->next - alloc->content) >= size)
		return (1);
	if (!(alloc->next) && (size_t)(pg_info->page_end - alloc->content) >= size)
		return (1);
	return (0);
}

int	find_realloc_diff_pg(t_list *alloc, t_list *pg, size_t size)
{
	t_page_info	*pg_info;
	t_page_info	*pg_next_info;

	if (!alloc || !pg || !size || alloc->next)
		return (0);
	if (!(pg->next))
		return (1);
	pg_info = (t_page_info *)(pg->content);
	pg_next_info = (t_page_info *)(pg->next->content);
	if ((size_t)(pg_next_info->alloc_start - alloc->content) >= size)
		return (1);
	return (0);
}

int	ft_mem_realloc_new_pg(t_list *alloc, t_list *pg, size_t size, int is_zone)
{
	t_page_info	*pg_info;
	t_page_info	*pg_next_info;
	size_t		len;

	if (!alloc || !pg || is_zone)
		return (0);
	pg_info = (t_page_info *)(pg->content);
	len = (size_t)(pg_info->page_end - alloc->content - alloc->size);
	if (!(pg->next))
		return (page_alloc_end(pg_info, size - len));
	pg_next_info = (t_page_info *)(pg->next->content);
	if (pg->next && (pg_next_info->alloc_start
			- alloc->content - size) > PG_MARGIN)
		return (page_alloc_end(pg_info, size - len));
	if (pg->next && (pg_next_info->alloc_start
			- alloc->content - size) <= PG_MARGIN)
		return (page_alloc_merge(pg));
	return (0);
}

void	*find_realloc(t_list *alloc, t_list *pg, size_t size, int is_zone)
{
	t_page_info	*pg_info;
	size_t		prev_size;
	int			ret1;
	int			ret2;
	int			ret3;

	pg_info = (t_page_info *)(pg);
	prev_size = alloc->size;
	ret1 = find_realloc_same_ele_pg(alloc, pg_info, size);
	ret2 = find_realloc_diff_pg(alloc, pg, size);
	ret3 = 0;
	if (ret1 == 1 || ret2 == 1)
	{
		alloc->size = size;
		if (ret1 == 1 && prev_size > size && alloc->next == 0)
			ret3 = page_trim_end(pg_info);
		if (ret2 == 1 && ret1 != 1)
			ret3 = ft_mem_realloc_new_pg(alloc, pg, size, is_zone) == 0;
		if (ret3 == 1)
			return (alloc->content);
	}
	return (0);
}
