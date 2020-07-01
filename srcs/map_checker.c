/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:03:25 by vduvinag          #+#    #+#             */
/*   Updated: 2020/06/25 23:15:00 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_check_borders(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '#')
			return (-1);
		i++;
	}
	return (0);
}

int		ft_check_line(char *line)
{
	int i;

	i = 0;
	if (line[i++] != '#')
		return (-2);
	while (line[i])
	{
		if (line[i] != '.' && line[i] != '#')
			return (-1);
		i++;
	}
	if (line[--i] != '#')
		return (-2);
	return (0);
}

void	ft_error(int code, char *line)
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
	exit(EXIT_FAILURE);
}

void	ft_norme(int code)
{
	if (code == 5)
		ft_putendl_fd("Error during open() ", 2);
	exit(EXIT_FAILURE);
}
