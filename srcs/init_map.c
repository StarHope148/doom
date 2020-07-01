/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:01:07 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/26 16:58:47 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	**ft_malloc_tab(t_env *wolf)
{
	char	**tab;
	int		i;

	tab = NULL;
	if ((tab = (char **)malloc(sizeof(char *) * wolf->mapdata.nbl)) == NULL)
		return (NULL);
	i = 0;
	while (i < wolf->mapdata.nbl)
	{
		tab[i] = NULL;
		if (!(tab[i] = (char *)malloc(sizeof(char) *
						(wolf->mapdata.nbcol + 1))))
			return (NULL);
		i++;
	}
	return (tab);
}

int		ft_retrieve_data(t_env *wolf, char *line)
{
	if (wolf->mapdata.map == NULL)
		if ((wolf->mapdata.map = ft_malloc_tab(wolf)) == NULL)
			return (-1);
	ft_strcpy(wolf->mapdata.map[wolf->mapdata.cur_line], line);
	wolf->mapdata.map[wolf->mapdata.cur_line][ft_strlen(line)] = '\0';
	wolf->mapdata.cur_line++;
	return (0);
}

void	ft_fill_map(t_env *wolf, int fd)
{
	char	*line;
	char	ret;
	int		i;

	i = 0;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_check_line(line) < 0 || i++ == 0 || i == wolf->mapdata.nbl)
		{
			if (ft_check_line(line) == -1)
				ft_error(3, line);
			if ((ft_check_line(line) == -2) || (ft_check_borders(line) == -1))
				ft_error(4, line);
		}
		if (ft_retrieve_data(wolf, line) == -1)
			ft_error(1, line);
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	if (wolf->mapdata.nbl < 3 || wolf->mapdata.nbcol < 3)
	{
		ft_putendl_fd("wrong map format", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_count_lines_columns(t_env *wolf, char *mapfile, int fd)
{
	char	*line;

	if ((fd = open(mapfile, O_RDONLY)) < 0)
		ft_norme(5);
	line = NULL;
	if ((get_next_line(fd, &line)) <= 0)
		ft_error(6, line);
	wolf->mapdata.nbcol = ft_strlen(line);
	ft_memdel((void **)&line);
	wolf->mapdata.nbl++;
	if (wolf->mapdata.nbcol > 100)
		ft_error(8, line);
	while (get_next_line(fd, &line) > 0)
	{
		if (wolf->mapdata.nbcol != (int)ft_strlen(line))
		{
			close(fd);
			ft_error(2, line);
		}
		wolf->mapdata.nbl++;
		ft_memdel((void **)&line);
	}
	if (close(fd) < 0)
		ft_error(7, line);
}

void	ft_init_map(t_env *wolf, char *mapfile)
{
	int fd;

	fd = 0;
	ft_count_lines_columns(wolf, mapfile, fd);
	if ((fd = open(mapfile, O_RDONLY)) < 0)
	{
		ft_putendl_fd("Error during open() ", 2);
		exit(EXIT_FAILURE);
	}
	ft_fill_map(wolf, fd);
	if (close(fd) < 0)
	{
		ft_putendl_fd("Error during close() ", 2);
		exit(EXIT_FAILURE);
	}
}
