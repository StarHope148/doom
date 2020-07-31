/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_crouch_jump_run_fly.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:28:34 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 01:10:37 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_movespeed(t_env *doom)
{
	if (doom->moves.running == TRUE &&
			doom->moves.crouching == FALSE)
		doom->moves.movespeed = RUN_RATIO * MOVE_SPEED;
	else if (doom->moves.running == FALSE)
		doom->moves.movespeed = MOVE_SPEED;
}

void	ft_crouch(t_env *doom)
{
	if (doom->moves.falling == FALSE && doom->moves.jumping == FALSE)
	{
		if (doom->moves.crouching == TRUE)
		{
			doom->moves.flying = FALSE;
			if (doom->cam.pos_z - INC_POS_Z >= MIN_CROUCH)
				doom->cam.pos_z -= INC_POS_Z;
		}
		else if (doom->moves.crouching == FALSE && doom->moves.flying == FALSE)
			doom->moves.raising = TRUE;
	}
}

void	ft_jump(t_env *doom)
{
	static int		duration;

	if (doom->moves.falling == FALSE && doom->moves.crouching == FALSE)
	{
		if (doom->moves.jumping == TRUE)
		{
			doom->moves.flying = FALSE;
			if (doom->cam.pos_z + INC_POS_Z <= MAX_JUMP)
				doom->cam.pos_z += INC_POS_Z;
			else if (duration < 5)
				duration++;
			else if (doom->moves.jumping == TRUE)
			{
				duration = 0;
				doom->moves.jumping = FALSE;
				doom->moves.falling = TRUE;
			}
		}
		else
			doom->moves.jumping = FALSE;
	}
	else if (doom->moves.crouching == TRUE)
		doom->moves.jumping = FALSE;
}

void	ft_reset_pos_z(t_env *doom)
{
	if (doom->moves.falling == TRUE)
	{
		if (doom->cam.pos_z - INC_POS_Z >= DEFAULT_POS_Z)
			doom->cam.pos_z -= INC_POS_Z;
		else
			doom->moves.falling = FALSE;
	}
	else if (doom->moves.raising && doom->moves.flying == FALSE)
	{
		if (doom->cam.pos_z + INC_POS_Z <= DEFAULT_POS_Z)
			doom->cam.pos_z += INC_POS_Z;
		else
			doom->moves.raising = FALSE;
	}
}

void	ft_fly(t_env *doom)
{
	if (doom->moves.up == TRUE)
	{
		doom->moves.flying = TRUE;
		if (doom->cam.pos_z + INC_POS_Z <= MAX_POS_Z + 0.01)
			doom->cam.pos_z += INC_POS_Z;
	}
	else if (doom->moves.down == TRUE)
	{
		doom->moves.flying = TRUE;
		if (doom->cam.pos_z - INC_POS_Z >= MIN_POS_Z)
			doom->cam.pos_z -= INC_POS_Z;
	}
}
