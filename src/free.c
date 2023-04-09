/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:38:13 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/09 17:06:38 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	ft_str_frerror(void *addr)
{
	ft_putstr_fd("malloc: *** error for object ", 2);
	ft_puthex_fd((size_t)addr, 2, 1);
	ft_putstr_fd(": pointer being freed was not allocated\n", 2);
	pthread_exit(0);
}

void	free(void *addr)
{
	int	ret;

	ret = 0;
	if (g_gen_info.is_tiny_alloc)
		ret = zone_mem_dealloc(addr, &(g_gen_info.tiny));
	if (!ret && g_gen_info.is_small_alloc)
		ret = zone_mem_dealloc(addr, &(g_gen_info.small));
	if (!ret)
		ret = mem_dealloc(addr);
	if (ret < 1)
		ft_str_frerror(addr);
}
