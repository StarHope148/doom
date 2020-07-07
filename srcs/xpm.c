/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 00:18:51 by czhang            #+#    #+#             */
/*   Updated: 2020/07/07 07:38:58 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
static char	*example2_xpm[] =
{
	"3 5 3 2",
	"  	c None",
	"..	c #3A32E4",
	".+	c #FFFFFF",
	"      ",
	"......",
	".+..  ",
	"    .+",
	"......"
}; */

void	error(t_env *wolf, char *message)
{
	ft_exit(wolf, EXIT_FAILURE, message);
}

void	init_xpm(t_env *wolf, t_xpm *xpm, char *firstline)
{
	int i;

	i = 0;
	xpm->w = ft_atoi(firstline);
	while (firstline[i] && firstline[i] != ' ')
		i++;
	while (firstline[i] == ' ')
		i++;
	xpm->h = ft_atoi(firstline + i);
	while (firstline[i] && firstline[i] != ' ')
		i++;
	while (firstline[i] == ' ')
		i++;
	xpm->colormax = ft_atoi(firstline + i);
	while (firstline[i] && firstline[i] != ' ')
		i++;
	while (firstline[i] == ' ')
		i++;
	xpm->nchar = ft_atoi(firstline + i);
	printf("h = %d, w = %d, colors = %d, nchar = %d, \n", xpm->h, xpm->w, xpm->colormax, xpm->nchar);
	if (xpm->h < 1 || xpm->w < 1 || xpm->colormax < 1 || xpm->nchar < 1)
		error(wolf, "Error xpm format");
}

int		color_to_hex(char *colorline, int i)
{
	while (colorline[i] == ' ' || colorline[i] == '\t')
		i++;
	while (colorline[i] && colorline[i] != ' ' && colorline[i] != '\t')
		i++;
	while (colorline[i] == ' ' || colorline[i] == '\t')
		i++;
	if (colorline[i] == '#')
		i++;
	return (strtol(colorline + i, NULL, 16));
}

int		get_hexpixel(t_xpm *xpm, char **file, int line, int i)
{
	int		color;
	char	**data;

	// l'image est stockee juste apres la derniere ligne des couleurs
	data = file + xpm->colormax + 1;
	color = -1;
	while (++color < xpm->colormax)
	{
		if (0 == ft_strncmp(file[color + 1],
							data[line] + i * xpm->nchar, xpm->nchar))
			return (color_to_hex(file[color + 1], xpm->nchar));
	}
	return (-1);
}

t_xpm	get_xpm(t_env *wolf, char **xpm_file)
{
	int		line;
	int		i;
	t_xpm	xpm;

	init_xpm(wolf, &xpm, xpm_file[0]);
	if (!(xpm.pixels = (int *)ft_memalloc(sizeof(int) * xpm.h * xpm.w)))
		error(wolf, "Error malloc in get_xpm()");
	line = -1;
	while (++line < xpm.h)
	{
		i = -1;
		while (++i < xpm.w)
		{
			xpm.pixels[line * xpm.w + i] =
									get_hexpixel(&xpm, xpm_file, line, i);
			if (xpm.pixels[line * xpm.w + i] == -1)
				error(wolf, "Error xpm format2");
		}
	}
	return (xpm);
}

/* void	print_pixeltab(t_xpm *xpm)
{
	int		i;

	i = -1;
	while (++i < xpm->h * xpm->w)
	{
		ft_putnbr(xpm->pixels[i]);
		ft_putchar(' ');
		if ((i + 1) % xpm->w == 0)
			ft_putchar('\n');
	}
} */
