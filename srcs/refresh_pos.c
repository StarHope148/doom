/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:34:19 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 01:04:35 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_refresh_new_pos(t_env *doom)
{
	resolve_on_fire(doom);
	set_movespeed(doom);
	ft_crouch(doom);
	ft_jump(doom);
	ft_fly(doom);
	ft_reset_pos_z(doom);
	ft_move(doom);
	ft_rotation(doom);
	ft_pick_up_items(doom);
	ft_firing_anim(doom);
}
