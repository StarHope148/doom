/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:34:19 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 17:50:55 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_check_dead(t_env *doom)
{
	static int	duration = 0;

	if (doom->chr.dead == TRUE)
	{
		if (duration < 500)
			draw_centered_text(doom, doom->txt.dead, 0.3);
		duration++;
	}
	else
		duration = 0;
}

void	ft_check_end_level(t_env *doom)
{
	static int	duration = 0;
	static int	end_level = FALSE;

	if (doom->map.data[(int)doom->cam.pos_y *
			doom->map.nbcol + (int)doom->cam.pos_x] == END_CASE)
	{
		end_level = TRUE;
		doom->chr.dead = FALSE;
	}
	if (end_level == TRUE)
	{
		draw_centered_text(doom, doom->txt.end_level, 0.3);
		duration++;
	}
	if (duration == 1000)
		ft_exit(doom, EXIT_SUCCESS, "Goodbye !");
}

void	ft_refresh_new_pos(t_env *doom)
{
	resolve_on_fire(doom);
	set_movespeed(doom);
	ft_crouch(doom);
	ft_jump(doom);
	ft_fly(doom);
	ft_reset_pos_z(doom);
	ft_move(doom);
	ft_check_end_level(doom);
	ft_rotation(doom);
	ft_pick_up_items(doom);
	ft_firing_anim(doom);
}
