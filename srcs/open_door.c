/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 04:49:08 by czhang            #+#    #+#             */
/*   Updated: 2020/07/06 23:27:25 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	anim_one_door(t_env *wolf, t_door *door)
{
	t_door	*d;
	double	duration;

	duration = get_time(wolf) - door->start_time;
	if (duration < DOOR_OPENING_DURATION)
	{
		d = door;
		wolf->map.alt[d->y][d->x] = d->start_alt + duration * d->speed;
	}
	else if (duration >= DOOR_OPENING_DURATION)
	{
		wolf->map.data[door->y][door->x] = '.';
		wolf->map.alt[door->y][door->x] = 1;
	}
}

void		animation_opening_door(t_env *wolf)
{
	t_door	*door;

	door = wolf->door;
	while (door)
	{
		anim_one_door(wolf, door);
		door = door->next;
	}
	door = wolf->door;
/* cleaning closed doors*/
	while (door)
	{
		if (wolf->map.data[door->y][door->x] == '.')
		{
			wolf->door = door->next;
			ft_memdel((void **)&door);
		}
		else
			door = door->next;
	}
}

static void	new_door(t_env *wolf, int door_y, int door_x, t_door *last)
{
	t_door	*d;

	if (!(d = (t_door *)ft_memalloc(sizeof(t_door))))
		ft_exit(wolf, EXIT_FAILURE, "Error malloc door opening");
	if (last == NULL)
		wolf->door = d;
	else if (last)
		last->next = d;
	d->start_time = get_time(wolf);
	d->start_alt = wolf->map.alt[door_y][door_x];
	d->speed = (MIN_ALTITUDE - d->start_alt) / (double)DOOR_OPENING_DURATION;
	d->x = door_x;
	d->y = door_y;
}

static void	init_door(t_env *wolf, int door_y, int door_x)
{
	t_door	*last;

	last = wolf->door;
	while (last && last->next)
		last = last->next;
	new_door(wolf, door_y, door_x, last);
}

void		resolve_door(t_env *wolf)
{
	int		y;
	int		x;
	double	angle;
	char	**d;

	d = wolf->map.data;
	y = (int)wolf->cam.pos_y;
	x = (int)wolf->cam.pos_x;
	angle = wolf->cam.angle;

	if ((angle <= -PI * 0.25 && angle >= -PI * 0.75) && d[y][x - 1] == 'D')
		x = x - 1;
	else if ((angle >= PI * 0.75 || angle <= -PI * 0.75) && d[y - 1][x] == 'D')
		y = y - 1;
	else if ((angle >= -PI * 0.25 && angle <= PI * 0.25) && d[y + 1][x] == 'D')
		y = y + 1;
	else if ((angle >= PI * 0.25 && angle <= PI * 0.75) && d[y][x + 1] == 'D')
		x = x + 1;
	else
		return ;
	init_door(wolf, y, x);
}