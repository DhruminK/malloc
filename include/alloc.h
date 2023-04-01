/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 11:42:31 by dkhatri           #+#    #+#             */
/*   Updated: 2023/04/01 16:26:06 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>

# define LARGE_ADDR	0xA0000
# define SMALL_ADDR	0x70000
# define TINY_ADDR	0x50000

# define PG_MARGIN	20

# define SMALL_MAX	80
# define TINY_MAX	40

typedef struct s_alloc_info
{
	void			*start;
	void			*end;
	t_list			*alloc;
	size_t			max;
}					t_alloc_info;

typedef struct s_page_info
{
	void			*page_start;
	void			*page_end;

	void			*alloc_start;
	t_list			*alloc;
}					t_page_info;

typedef struct s_gen_info
{
	int				is_alloc;
	int				pg_size;
	t_page_info		tiny;
	t_page_info		small;
	t_list			*mem;
}					t_gen_info;

extern t_gen_info	g_gen_info;

#endif
