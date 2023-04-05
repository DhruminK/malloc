/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:10:33 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/04 17:04:45 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

int	alloc_mmap(void *addr, size_t *len)
{
	void	*p;
	size_t	page_len;
	int		pg;

	if (!addr || !len || !*len)
		return (-1);
	pg = getpagesize();
	page_len = ((size_t)(*len / pg)) * pg;
	if (*len % pg)
		page_len += pg;
	p = mmap(addr, page_len, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON | MAP_FIXED, -1, 0);
	if (p == MAP_FAILED)
		return (-1);
	*len = page_len;
	return (0);
}
