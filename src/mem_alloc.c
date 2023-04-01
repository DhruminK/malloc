/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:15:24 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/01 17:30:45 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*ft_mem_alloc_init(t_list *prev, void *addr, size_t size)
{
	t_list *ele;
	
	if (prev)
		ele = prev->content + prev->size;
	else
		ele = (t_list *)addr;
	ele->content = ele + sizeof(t_list);
	ele->size = size;
	if (prev)
	{
		ele->next = prev->next;
		prev->next = ele;
	}
	return (ele->content);
}

void	*ft_mem_alloc_page_end(t_list *pg, size_t size, t_list *prev_alloc)
{
	size_t		len;
	size_t		ret;
	t_page_info	*pg_info;
	t_page_info	*pg_next_info;

	if (!pg || !prev_alloc)
		return (0);
	pg_info = (t_page_info*)(pg->content);
	size = size + sizeof(t_list);
	len = (size_t)(pg_info->page_end - prev_alloc->content - prev_alloc->size);
	if (!(pg->next) && page_alloc_end(pg_info, size - len) == -1)
		return (0);
	if (!(pg->next))
		return (ft_mem_alloc_init(prev_alloc, 0, size - sizeof(t_list)));
	pg_next_info = (t_page_info*)(pg->next->content);
	ret = pg_next_info->alloc_start - pg_info->page_end - len;
	if (ret > size + PG_MARGIN && page_alloc_end(pg_info, size - len) == -1)
		return (0);
	if (ret < size + PG_MARGIN && ret >= size && page_alloc_merge(pg) == -1)
		return (0);
	return (ft_mem_alloc_init(prev_alloc, 0, size - sizeof(t_list)));
}

void	*ft_mem_alloc_mid(t_list *prev_alloc, t_list *pg, size_t size)
{
	t_page_info	*pg_info;
	size_t		len;

	if (!prev_alloc || !pg)
		return (0);
	len = (size_t)(prev_alloc->content + prev_alloc->size);
	if (prev_alloc->next && (size_t)(prev_alloc->next - len)
			>= size + sizeof(t_list))
		return (ft_mem_alloc_init(prev_alloc, 0, size));
	else if (prev_alloc->next)
		return (0);
	pg_info = (t_page_info *)(pg->content);
	if ((size_t)(pg_info->page_end - len) > size + sizeof(t_list))
		return (ft_mem_alloc_init(prev_alloc, 0, size));
	return (ft_mem_alloc_page_end(pg, size, prev_alloc));
}

void	*ft_mem_alloc_start(t_list *pg, size_t size)
{
	t_list		*ele;
	t_page_info	*pg_info;
	void		*addr;

	if (!pg)
	{
		addr = (void *)(LARGE_ADDR);
		if (g_gen_info.mem && (page_alloc_start() == -1))
			return (0);
		else if (!(g_gen_info.mem) && 
				(new_page_alloc(&(g_gen_info.mem), &addr,
								size + sizeof(t_list)) == -1))
			return (0);
	}
	ft_lst_add_front(&(pg->alloc), (t_list *)(pg->alloc_start));
	return (ft_mem-alloc_init(0, pg->alloc->start, size));
}
