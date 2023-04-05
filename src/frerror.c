/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frerror.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:36:33 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/04 15:10:57 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*ft_str_frerror(void *addr)
{
	ft_putstr_fd("malloc: *** error for object ", 2);
	ft_puthex_fd((size_t)addr, 2, 0);
	ft_putstr_fd(": pointer being freed was not allocated\n", 2);
	ft_putstr_fd("malloc: *** set a breakpoint in malloc_error_break"
		" to debug", 2);
	pthread_exit(0);
}
