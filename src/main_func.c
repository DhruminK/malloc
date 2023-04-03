/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:30:24 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/03 17:54:11 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

t_gen_info	g_gen_info;

void	*malloc(size_t size)
{
	void	*addr;

	if (g_gen_info.is_alloc == 0)
		gen_info_init();
	if (!size)
		return (0);
	addr = 0;
	if (size < TINY_MAX)
		addr = zone_alloc(size, &(g_gen_info.tiny));
	if (!addr && size < SMALL_MAX)
		addr = zone_alloc(size, &(g_gen_info.small));
	if (!addr)
		addr = large_alloc(size);
	return (addr);
}

void	free(void *addr)
{
	int			ret;

	if (!addr)
		return ;
	ret = free_check_zones(addr);
	if (!ret)
		ret = large_dealloc(addr);
	if (ret == -1)
		ft_str_frerror();
}

void	*realloc(void *addr, size_t size)
{
	int		ret;
	void	*n_addr;

	if (!addr && !size)
		return (0);
	if (!addr)
		return (malloc(size));
	if (!size)
	{
		free(addr);
		return (0);
	}
	ret = 0;
	n_addr = (zone_realloc(addr, size, &ret));
	if (!n_addr && ret == -1)
	{
		ft_str_frerror();
		return (0);
	}
	ret = 0;
	n_addr = (zone_realloc(addr, size, &ret));
	if (!n_addr && ret == -1)
		ft_str_frerror();
	return (n_addr);
}
