/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:02:11 by dkhatri           #+#    #+#             */
/*   Updated: 2023/03/30 16:03:30 by dkhatri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include "helper_func.h"

//# define LST_SIZE	sizeof(t_mem_alloc) + sizeof(t_list)
//# define PAGE_SIZE	sizeof(t_page_info) + sizeof(t_list)
# define LARGE_ADDR	0xA000
# define SMALL_ADDR	0x7000
# define TINY_ADDR	0x5000

# define SMALL_MAX	80
# define TINY_MAX	40

typedef struct s_mem_alloc
{
	void			*start;
	void			*data_start;
	void			*end;
}					t_mem_alloc;

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
	t_alloc_info	tiny;
	t_alloc_info	small;
	t_list			*mem;
}					t_gen_info;

extern t_gen_info	g_gen_info;

void				*zone_mem_alloc(size_t size, t_alloc_info *alloc);
int					find_size(t_list *a, void *end,
						t_list **alloc, size_t size);
void				*find_in_pages(size_t size);
int					new_page_alloc_end(t_page_info *pg_info,
						size_t size, void *alloc_end);
int					new_page_alloc(t_list *pg, size_t size);
int					new_page_start_alloc(void *addr,
						size_t size, t_list **alloc);
int					ft_insert_mem_info(t_list *ele, void *start, size_t size,
						t_list **head);
int					alloc_mmap(void *addr, size_t *len);

#endif
