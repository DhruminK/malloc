/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:37:55 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/13 17:09:52 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include <string.h>

#define M 1024

void	print(char *s)
{
	write(1, s, strlen(s));
}

int	main(void)
{
	char	*addr1;
	char	*addr2;
	char	*addr3;

	addr1 = malloc(16 * M * M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = malloc(16 * M * M);
	write(1, "HERE\n", 5);
	addr3 = realloc(addr1, 128 * M * M);
	return (0);
	addr3[127 * M * M] = 42;
	print(addr3);
	return (0);
}
