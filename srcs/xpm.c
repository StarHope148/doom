/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 00:18:51 by czhang            #+#    #+#             */
/*   Updated: 2020/07/09 05:59:12 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	*xpm_error(t_xpm *xpm, char *message)
{
	if (message)
	{
		if (xpm->filename)
		{
			ft_putstr_fd(message, 2);
			ft_putstr_fd(" for ", 2);
			ft_putendl_fd(xpm->filename, 2);
		}
		else
			ft_putendl_fd(message, 2);
	}
	ft_free_xpm(xpm);
	return (NULL);
}


int		check_init(t_xpm *xpm, char *line, int num)
{
	if (num == 4 && (xpm->nchar = ft_strlen(line) - 13) < 1)
		return (-1);
	else if (num == xpm->colormax + 4 && *line != '/')
	{
		if (xpm->nchar != (int)ft_strlen(line) - 13)
			return (-1);
		xpm->colormax++;
	}
	else if (num == xpm->colormax + 5
						&& (xpm->w = (ft_strlen(line) - 2) / xpm->nchar) < 1)
		return (-1);
	else if (num == xpm->colormax + xpm->h + 5 && *line != '/' && *line != '}')
	{
		if (xpm->w != ((int)ft_strlen(line) - 2) / xpm->nchar)
			return (-1);
		xpm->h++;
	}
	return (0);
}

int		cmp_file_info(t_xpm *xpm, char *info)
{
	int i;

	if(ft_atoi(info + 1) != xpm->w)
		return (-1);
	i = 2;
	while (info[i] && info[i] != ' ')
		i++;
	while (info[i] == ' ')
		i++;
	if (ft_atoi(info + i) != xpm->h)
		return (-1);
	while (info[i] && info[i] != ' ')
		i++;
	while (info[i] == ' ')
		i++;
	if (ft_atoi(info + i) != xpm->colormax)
		return (-1);
	while (info[i] && info[i] != ' ')
		i++;
	while (info[i] == ' ')
		i++;
	if (ft_atoi(info + i) != xpm->nchar)
		return (-1);
	return (0);
}

int		xpm_fill(t_xpm *xpm, char *line, int num)
{
	int	i;
	int	color;

	if (num == 3)
		return (cmp_file_info(xpm, line));
	else if (3 < num && num < xpm->colormax + 4)
	{
		i = -1;
		while (++i < xpm->nchar + 1)
			xpm->color[xpm->colormax + 3 - num][i] = line[1 + i];
		i--;
		while (++i < xpm->nchar + 8)
			xpm->color[xpm->colormax + 3 - num][i] = line[i + 3];
	}
	else if (xpm->colormax + 4 < num && num < xpm->colormax + 5 + xpm->h)
	{
		i = -1;
		while (++i < xpm->w)
		{
			color = -1;
			while (++color < xpm->colormax)
			{
				if (!ft_strncmp(1 + line + xpm->nchar * i, xpm->color[color], xpm->nchar))
				{
					xpm->pixels[(num - xpm->colormax - 5) * xpm->w + i] =
							(Uint32)strtoul(xpm->color[color] + 2 + xpm->nchar, NULL, 16);
					xpm->pixels[(num - xpm->colormax - 5) * xpm->w + i] <<= 8;
					break;
				}
				else if (color == xpm->colormax - 1)
					return (-1);
			}
		}
	}
	//printf("fileline = %d, h = %d, w = %d, colors = %d, nchar = %d, \n", num, xpm->h, xpm->w, xpm->colormax, xpm->nchar);
	return (0);
}

int		each_line(t_xpm *xpm, int fd, int (*f)(t_xpm *x, char *l, int n))
{
	char	*line;
	int		num_line;
	int		error_in_function;

	lseek(fd, 0, SEEK_SET);
	error_in_function = 0;
	num_line = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (f(xpm, line, num_line++) < 0)
			error_in_function++;
		ft_memdel((void **)&line);
	}
	//ft_putnbr(error_in_function);
	//ft_putendl("");
	if (error_in_function)
		return (-1);	
	return (0);
}
int		init_malloc(t_xpm *xpm)
{
	int	i;

	if (!(xpm->color = (char **)ft_memalloc(sizeof(char *) * xpm->colormax + 1)))
		return (-1);
	i = -1;
	while (++i < xpm->colormax)
	{
		if (!(xpm->color[i] = (char *)ft_memalloc(sizeof(char) * (9 + xpm->nchar))))
			return (-1);
		xpm->color[i][xpm->nchar + 8] = '\0';
	}
	if (!(xpm->pixels = (Uint32 *)ft_memalloc(sizeof(int) * xpm->h * xpm->w)))
		return (-1);
	if (xpm->h < 1 || xpm->w < 1 || xpm->colormax < 1 || xpm->nchar < 1)
		return (-1);
	return (0);
}

void	print_tab(t_xpm *xpm)
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
}

t_xpm	*get_xpm(char *filename)
{
	t_xpm	*xpm;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (xpm_error(0, "Error open xpm"));
	if ((xpm = (t_xpm *)ft_memalloc(sizeof(t_xpm))) == NULL)
		return (xpm_error(xpm, "Error malloc in get_xpm()"));
	xpm->colormax = 1;
	xpm->w = 1;
	xpm->h = 1;
	xpm->filename = ft_strdup(filename);
	if (each_line(xpm, fd, check_init) < 0 || init_malloc(xpm) < 0
			|| each_line(xpm, fd, xpm_fill) < 0 || close(fd) < 0)
		return (xpm_error(xpm, "Please only use XPM3 format"));
	//print_tab(xpm);
	fd = -1;
	while (++fd < xpm->colormax && xpm->color[fd])
		ft_memdel((void **)&xpm->color[fd]);
	ft_memdel((void **)&xpm->color);
	return (xpm);
}
