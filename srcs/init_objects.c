/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:25:08 by jcanteau          #+#    #+#             */
/*   Updated: 2020/07/31 02:43:08 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			ft_check_remove_status_obj(t_object *obj)
{
	t_object	*current;
	t_object	*next;

	current = obj;
	next = current->next;
	while (current != NULL && next != NULL)
	{
		if (next->data.to_remove)
		{
			current->next = next->next;
			ft_memdel((void **)&(next));
		}
		current = current->next;
		if (current != NULL)
			next = current->next;
	}
}

void			ft_add_object(t_env *doom, t_point pos, char type)
{
	t_object	*tmp;

	tmp = &doom->obj;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->data.type == 0)
	{
		tmp->data.pos.x = pos.x + 0.5;
		tmp->data.pos.y = pos.y + 0.5;
		tmp->data.type = type;
	}
	else
	{
		if ((tmp->next = ft_memalloc(sizeof(t_object))) == NULL)
			ft_exit(doom, EXIT_FAILURE, "Error in ft_memalloc");
		tmp = tmp->next;
		tmp->data.pos.x = pos.x + 0.5;
		tmp->data.pos.y = pos.y + 0.5;
		tmp->data.type = type;
	}
}

void			ft_count_objects(t_env *doom)
{
	t_point		pos;
	char		cell_type;

	pos.y = 0;
	while (pos.y < doom->map.nbl)
	{
		pos.x = 0;
		while (pos.x < doom->map.nbcol)
		{
			cell_type = doom->map.data[pos.y * doom->map.nbcol + pos.x];
			if (cell_type == BARREL || cell_type == HEALTH_POTION || cell_type
					== KEY || cell_type == TORCH || cell_type == STATUE)
				ft_add_object(doom, pos, cell_type);
			pos.x++;
		}
		pos.y++;
	}
}