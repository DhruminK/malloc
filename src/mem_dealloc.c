/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:22:32 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/08 18:12:51 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	mem_dealloc_gen(t_list *pg, t_page_info *pg_info, t_list *alloc)
{
	t_list		**head;
	t_list		*ele;
	t_page_info	*pgi;

	if (!alloc)
		return ;
	pgi = pg_info;
	if (!pgi)
		pgi = (t_page_info *)(pg->content);
	ele = (t_list *)(pgi->alloc);
	while (ele && ele->next != alloc)
		ele = ele->next;
	head = (t_list **)&(pgi->alloc);
	if (ele)
		head = &(ele->next);
	*head = alloc->next;
	if (!pg_info)
		ft_page_div(pg, ele);
}

int	mem_dealloc(void *addr)
{
	t_list		*pg;
	t_list		*alloc;

	if (!addr)
		return (0);
	pg = 0;
	alloc = 0;
	if (find_addr(g_gen_info.large, addr, &pg, &alloc) < 1)
		return (-1);
	mem_dealloc_gen(pg, 0, alloc);
	return (1);
}

int	zone_mem_dealloc(void *addr, t_page_info *pg_info)
{
	t_list		*ele;
	int			ret;

	if (!addr || !pg_info)
		return (0);
	ret = find_addr_in_pg(pg_info, addr, &ele);
	if (ret < 1)
		return (ret);
	mem_dealloc_gen(0, pg_info, ele);
	return (1);
}
