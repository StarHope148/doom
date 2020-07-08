/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 00:18:51 by czhang            #+#    #+#             */
/*   Updated: 2020/07/08 02:50:32 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void	error(t_env *doom, char *message)
{
	//peut etre pas exit non plus vu que c pas trop grave de fail chargement xpm
	if (doom)
		ft_exit(doom, EXIT_FAILURE, message);
	ft_putendl("error or warning xpm");
}

/* int		color_to_hex(char *colorline, int i)
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
	data = file + xpm->clrmax + 1;
	color = -1;
	while (++color < xpm->clrmax)
	{
		if (0 == ft_strncmp(file[color + 1],
							data[line] + i * xpm->nchar, xpm->nchar))
			return (color_to_hex(file[color + 1], xpm->nchar));
	}
	return (-1);
} */

void	init_check(t_xpm *xpm, char *l)
{
	if (xpm->fileline == 0 && ft_strncmp("/* XPM */", l, 9) != 0)
		ft_putendl_fd("Warning : xpm file may have a wrong format", 2);
	else if (xpm->fileline == 1 && ft_strlen(l + 19) == 0)
		ft_putendl_fd("Warning : xpm file may have no name", 2);
	else if (xpm->fileline == 2 && l[0] != '/')
		ft_putendl_fd("Warning : xpm file may have a wrong format", 2);
	else if (xpm->fileline == 3 && ft_strlen(l) < 7)
		ft_putendl_fd("Warning : xpm file may have a wrong format", 2);
	else if (xpm->fileline == 4 && (xpm->nchar = ft_strlen(l) - 10) < 1)
		ft_putendl_fd("Warning : xpm file may have a wrong format", 2);
	else if (l[0] != '/' && (int)ft_strlen(l) - 10 == xpm->nchar)
		xpm->clrmax++;
	else if (ft_strncmp("/* pixels */", l, 12) != 0)
		ft_putendl_fd("Warning : xpm file may have a wrong format", 2);
	else if (xpm->fileline == xpm->clrmax + 5
					&& (xpm->w = (ft_strlen(l) - 2) / xpm->nchar) < 1)
		ft_putendl_fd("Warning : xpm file may have a wrong format", 2);
	else if (xpm->w == ((int)ft_strlen(l) - 2) / xpm->nchar && l[0] != '}')
		xpm->h++;
}

int		iter_line(t_xpm *xpm, int fd, char *l, void (*f)(t_xpm *x, char *l))
{
	int	ret_gnl;

	if ((ret_gnl = get_next_line(fd, &l)) < 0)
		return (ret_gnl);
	f(xpm, l);
	ft_memdel((void **)&l);
	return (ret_gnl);
}

void	each_line(t_xpm *xpm, char *xpmfile, void (*f)(t_xpm *x, char *l))
{
	char	*line;
	int		fd;

	xpm->fileline = 0;
	if (f == init_check)
	{
		xpm->clrmax = 1;
		xpm->h = 1;
	}
	if ((fd = open(xpmfile, O_RDONLY)) < 0)
		error(0, 0);
	line = NULL;
	while (iter_line(xpm, fd, line, f) > 0)
		xpm->fileline++;
	if (close(fd) < 0)
		error(0, 0);
}

void	init_xpm(t_env *doom, t_xpm *xpm, char *firstline)
{
	int i;

	i = 1;
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
	xpm->clrmax = ft_atoi(firstline + i);
	while (firstline[i] && firstline[i] != ' ')
		i++;
	while (firstline[i] == ' ')
		i++;
	xpm->nchar = ft_atoi(firstline + i);
	printf("h = %d, w = %d, colors = %d, nchar = %d, \n", xpm->h, xpm->w, xpm->clrmax, xpm->nchar);
	if (xpm->h < 1 || xpm->w < 1 || xpm->clrmax < 1 || xpm->nchar < 1)
		error(doom, "Error xpm format");
}

t_xpm	*get_xpm(t_env *doom, char *xpmfile)
{
	t_xpm	*xpm;

	if ((xpm = (t_xpm *)ft_memalloc(sizeof(t_xpm))) == NULL)
		error(doom, "Error malloc in get_xpm()");
	each_line(xpm, xpmfile, init_check);
	//init_xpm(doom, xpm, );
/* 	if (!(xpm->pixels = (int *)ft_memalloc(sizeof(int) * xpm->h * xpm->w)))
		error(doom, "Error malloc in  get_xpm()");
	line = -1;
	while (++line < xpm->h)
	{
		i = -1;
		while (++i < xpm->w)
		{
			xpm->pixels[line * xpm->w + i] =
									get_hexpixel(xpm, xpmfile, line, i);
			if (xpm->pixels[line * xpm->w + i] == -1)
				error(doom, "Error xpm format2");
		}
	}
 */	return (xpm);
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
