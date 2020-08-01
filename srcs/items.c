/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 06:15:12 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/02 00:11:19 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		ft_pick_up_health_potion(t_env *doom, t_object *tmp)
{
	if (tmp->data.type == HEALTH_POTION && tmp->data.dist <= 0.5)
	{
		if (ft_restore_health(doom, HEALTH_POTION_AMOUNT) == TRUE)
		{
			if ((FMOD_System_PlaySound(doom->sound.system, doom->sound.life_up,
					NULL, 0, NULL)) != FMOD_OK)
				perror("Error in FMOD_System_PlaySound for life_up ");
			tmp->data.to_remove = TRUE;
			doom->map.data[(int)tmp->data.pos.y *
				doom->map.nbcol + (int)tmp->data.pos.x] = EMPTY;
		}
	}
}

void		ft_pick_up_key(t_env *doom, t_object *tmp)
{
	if (tmp->data.type == KEY && tmp->data.dist <= 0.5)
	{
		if (doom->chr.carried_key == FALSE)
		{
			doom->chr.carried_key = TRUE;
			tmp->data.to_remove = TRUE;
			doom->map.data[(int)tmp->data.pos.y *
					doom->map.nbcol + (int)tmp->data.pos.x] = EMPTY;
		}
	}
}

void		ft_pick_up_items(t_env *doom)
{
	t_object	*tmp;

	tmp = &doom->obj;
	while (tmp != NULL)
	{
		ft_pick_up_health_potion(doom, tmp);
		ft_pick_up_key(doom, tmp);
		tmp = tmp->next;
	}
}
