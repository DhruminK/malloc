/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:51:20 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/04 12:24:02 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	ft_show_page_alloc(t_page_info *pg_info)
{
	t_list	*alloc;

	if (!pg_info || !(pg_info->alloc))
		return ;
	alloc = pg_info->alloc;
	while (alloc)
	{
		ft_puthex_fd((size_t)(alloc->content), 1, 1);
		ft_putstr_fd(" - ", 1);
		ft_puthex_fd((size_t)(alloc->content + alloc->size - 1), 1, 1);
		ft_putstr_fd(" : ", 1);
		ft_putunbr_fd(alloc->size, 1);
		if (alloc->size > 1)
			ft_putstr_fd(" bytes\n", 1);
		else
			ft_putstr_fd(" byte\n", 1);
		ft_putchar_fd('\n', 1);
		alloc = alloc->next;
	}
}

void	ft_show_zone_alloc(char *str, size_t addr,
			t_page_info *pg_info, t_list *pg)
{
	if (!pg_info || !pg)
		return ;
	if (str)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" : ", 1);
		ft_puthex_fd(addr, 1, 1);
		ft_putchar_fd('\n', 1);
	}
	if (pg_info)
		return (ft_show_page_alloc(pg_info));
	while (pg)
	{
		pg_info = (t_page_info *)(pg->content);
		ft_show_page_alloc(pg_info);
		pg = pg->next;
	}
}

void	show_alloc_mem(void)
{
	ft_show_zone_alloc("TINY", (size_t)TINY_ADDR,
		&(g_gen_info.tiny), 0);
	ft_show_zone_alloc("SMALL", (size_t)SMALL_ADDR,
		&(g_gen_info.small), 0);
	ft_show_zone_alloc("LARGE", (size_t)LARGE_ADDR,
		0, g_gen_info.mem);
}
