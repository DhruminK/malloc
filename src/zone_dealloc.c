#include "alloc.h"

int	find_alloc(t_list *al, void *addr, void *end, t_list **a)
{
	t_mem_alloc	*mem;

	if (!al || !addr || !a)
		return (0);
	if (addr >= end)
		return (0);
	while (al)
	{
		mem = (t_mem_alloc *)(al->content);
		*a = al;
		if (mem->data_start == addr)
			return (1);
		if (mem->end > addr)
			return (-1);
		al = al->next;
	}
	return (-1);
}
