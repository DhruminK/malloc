/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_helper_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:43:11 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/08 10:56:31 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	page_info_disp(t_page_info *pg_info)
{
	if (!pg_info)
		return ;
	ft_putstr_fd("PAGE START : ", 1);
	ft_puthex_fd(pg_info->page_start, 1, 1);
	ft_putstr_fd(" - ", 1);
	ft_puthex_fd(pg_info->page_end, 1, 1);
	ft_putstr_fd("\nALLOC START : ", 1);
	ft_puthex_fd(pg_info->alloc_start, 1, 1);
	ft_putstr_fd("\tALLOC : ", 1);
	ft_puthex_fd(pg_info->alloc, 1, 1);
	ft_putstr_fd("\n", 1);
}

void	page_disp(t_list *pg)
{
	while (pg)
	{
		page_info_disp((t_page_info *)(pg->content));
		pg = pg->next;
	}
}
