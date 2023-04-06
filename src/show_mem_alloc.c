/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:42:44 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/06 19:29:38 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	ft_alloc_print(t_page_info *pg_info)
{
	t_list	*ele;
	size_t	start;
	size_t	end;

	if (!pg_info)
		return ;
	ele = (t_list *)(pg_info->alloc);
	while (ele)
	{
		start = (size_t)(ele->content);
		end = (size_t)(ele->content + ele->size);
		ft_puthex_fd(start, 1, 1);
		ft_putstr_fd(" - ", 1);
		ft_puthex_fd(end, 1, 1);
		ft_putstr_fd(" : ", 1);
		ft_putunbr_fd(end - start, 1);
		if (end - start > 1)
			ft_putstr_fd(" bytes\n", 1);
		else
			ft_putstr_fd(" byte\n", 1);
		ele = ele->next;
	}
}

void	print_zone(char *str, int is_alloc, t_page_info *pg_info)
{
	ft_putstr_fd(str, 1);
	if (!is_alloc)
		ft_putstr_fd("0", 1);
	else
		ft_puthex_fd((size_t)(pg_info->page_start), 1, 1);
	ft_putchar_fd('\n', 1);
	if (is_alloc)
		ft_alloc_print(pg_info);
}

void	show_alloc_mem(void)
{
	t_list		*pg;
	t_page_info	*pg_info;

	print_zone("TINY : ", g_gen_info.is_tiny_alloc, &(g_gen_info.tiny));
	print_zone("SMALL : ", g_gen_info.is_small_alloc, &(g_gen_info.small));
	ft_putstr_fd("LARGE : ", 1);
	ft_puthex_fd((size_t)g_gen_info.large, 1, 1);
	ft_putchar_fd('\n', 1);
	pg = g_gen_info.large;
	while (pg)
	{
		pg_info = (t_page_info *)(pg->content);
		ft_alloc_print(pg_info);
		pg = pg->next;
	}
}
