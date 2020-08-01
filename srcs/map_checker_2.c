/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:08:55 by jcanteau          #+#    #+#             */
/*   Updated: 2020/08/01 16:24:43 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		precheck_one_2(char *l, int p, int i)
{
	if (l[p + i] != WALL && l[p + i] != EMPTY && l[p + i] != DOOR &&
			l[p + i] != TORCH && l[p + i] != OBJECT && l[p + i] != GRID &&
			l[p + i] != BARREL && l[p + i] != BUTTON_OFF &&
			l[p + i] != BUTTON_ON && l[p + i] != DOOR_OPENED &&
			l[p + i] != HEALTH_POTION && l[p + i] != KEY && l[p + i] != STATUE
			&& l[p + i] != END_CASE && l[p + i] != SPAWN)
		return (-1);
	else
		return (0);
}

int		ft_check_line_2(char *l, int i)
{
	if (l[i] != EMPTY && l[i] != WALL && l[i] != DOOR && l[i] != OBJECT &&
			l[i] != TORCH && l[i] != GRID && l[i] != BARREL &&
			l[i] != BUTTON_OFF && l[i] != BUTTON_ON && l[i] != DOOR_OPENED
			&& l[i] != HEALTH_POTION && l[i] != KEY && l[i] != STATUE &&
			l[i] != END_CASE && l[i] != SPAWN)
		return (-1);
	else
		return (0);
}

void	ft_error(t_map *m, int code, char *line)
{
	if (code == 1)
		ft_putendl_fd("error during malloc of map", 2);
	if (code == 2)
		ft_putendl_fd("Please use a rectangle map", 2);
	if (code == 3)
		ft_putendl_fd("map format is invalid", 2);
	if (code == 4)
		ft_putendl_fd("Your map is missing borders, BUILD THAT WALL", 2);
	if (code == 5)
		ft_putendl_fd("Error during open()", 2);
	if (code == 6)
		ft_putendl_fd("map is empty", 2);
	if (code == 7)
		ft_putendl_fd("Error during close()", 2);
	if (code == 8)
		ft_putendl_fd("Map is too big", 2);
	ft_memdel((void **)&line);
	ft_free_map(m);
	exit(EXIT_FAILURE);
}

void	ft_norme(int code)
{
	if (code == 5)
		ft_putendl_fd("Error during open() ", 2);
	exit(EXIT_FAILURE);
}
