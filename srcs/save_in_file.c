/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_in_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 00:42:18 by czhang            #+#    #+#             */
/*   Updated: 2020/08/01 19:44:57 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

size_t	pseudo_log10(int n)
{
	size_t	log;

	log = 0;
	if (n < 0)
		log++;
	while (n / 10 != 0)
	{
		log++;
		n /= 10;
	}
	return (log);
}

size_t	get_filesize(t_map *map)
{
	size_t		n;
	int			y;
	int			x;

	n = map->nbcol * map->nbl * 6 - 1;
	y = -1;
	while (++y < map->nbl)
	{
		x = -1;
		while (++x < map->nbcol)
		{
			n += pseudo_log10(map->bright[y * map->nbcol + x]);
			n += pseudo_log10(map->alt[y * map->nbcol + x]);
		}
	}
	return (n);
}

void	pseudo_itoa(char *str0, int n, size_t *i)
{
	char	*str;
	int		len;

	str = str0 + *i;
	len = 1 + pseudo_log10(n);
	*i += len;
	if (n < 0)
		str[0] = '-';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
}

void	fill_str(t_map *map, char *str)
{
	t_point	pos;
	size_t	i;

	i = 0;
	pos.y = -1;
	while (++pos.y < map->nbl)
	{
		pos.x = -1;
		while (++pos.x < map->nbcol)
		{
			str[i++] = map->data[pos.y * map->nbcol + pos.x];
			str[i++] = ' ';
			pseudo_itoa(str, map->bright[pos.y * map->nbcol + pos.x], &i);
			str[i++] = ' ';
			pseudo_itoa(str, map->alt[pos.y * map->nbcol + pos.x], &i);
			if (pos.x < map->nbcol - 1)
				str[i++] = '\t';
			else if (pos.x == map->nbcol - 1 && pos.y == map->nbcol - 1)
				str[i] = '\0';
			else if (pos.x == map->nbcol - 1 && pos.y < map->nbcol - 1)
				str[i++] = '\n';
		}
	}
}

void	save_in_file(t_env *doom)
{
	int		fd;
	char	*str;
	size_t	file_size;

	if ((fd = open("new.map", O_RDWR | O_CREAT, 0664)) < 0)
		ft_exit(doom, EXIT_FAILURE, "Error open in save_in_file()");
	file_size = get_filesize(&doom->map);
	if ((str = (char *)ft_memalloc((file_size + 1) * sizeof(char))) == NULL)
		ft_exit(doom, EXIT_FAILURE, "Error malloc in save_in_file()");
	fill_str(&doom->map, str);
	if (write(fd, str, file_size) != (int)file_size)
		ft_exit(doom, EXIT_FAILURE, "Error write in save_in_file()");
	ft_memdel((void **)&str);
	if (close(fd) < 0)
		ft_exit(doom, EXIT_FAILURE, "Error close in save_in_file()");
}
