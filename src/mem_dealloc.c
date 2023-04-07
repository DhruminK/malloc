/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:22:32 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/07 17:29:47 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	mem_dealloc(void *addr)
{
	t_list		*pg;
	t_list		*alloc;
	t_list		*ele;
	t_list		**head;
	t_page_info	*pg_info;

	if (!addr)
		return (0);
	pg = 0;
	alloc = 0;
	if (find_addr(g_gen_info.large, addr, &pg, &alloc) < 1)
		return (-1);
	pg_info = (t_page_info *)(pg->content);
	ele = (t_list *)(pg_info->alloc);
	while (ele && ele != alloc && ele->next != alloc)
		ele = ele->next;
	head = (t_list **)&(pg_info->alloc);
	if (ele != alloc)
		head = &(ele->next);
	*head = alloc->next;
	ft_page_div(pg, ele);
	return (1);
}

int	zone_mem_dealloc(void *addr, t_page_info *pg_info)
{
	t_list		*ele;
	t_list		*prev;
	t_list		**head;
	int			ret;

	if (!addr || !pg_info)
		return (0);
	ret = find_addr_in_pg(pg_info, addr, &ele);
	if (ret < 1)
		return (ret);
	prev = (t_list *)pg_info->alloc;
	while (prev && prev != ele && prev->next != ele)
		prev = prev->next;
	head = (t_list **)&(pg_info->alloc);
	if (prev->next == ele)
		head = &(prev->next);
	*head = ele->next;
	return (1);
}
