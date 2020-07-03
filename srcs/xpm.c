/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhang <czhang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 00:18:51 by czhang            #+#    #+#             */
/*   Updated: 2020/06/28 03:56:47 by czhang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* XPM */
static char * example_xpm[] = {
"24 20 3 1",
" 	c None",
".	c #3A32E4",
"+	c #FFFFFF",
"                        ",
"    ..                  ",
"   ....                 ",
"  ......++++++++        ",
" .........+++++++       ",
" ..........+++++++      ",
" ............++++++     ",
" .............++++++    ",
"  ..............++++    ",
"   +.............+++    ",
"   ++.............++    ",
"   +++.............+    ",
"   +++++.............   ",
"   ++++++.............. ",
"   ++++++++............ ",
"   +++++++++........... ",
"    +++++++++.........  ",
"     ++++++++++.......  ",
"      ++++++++++.....   ",
"       +++++++++ ...    "};

static char * example2_xpm[] = {
"3 5 3 2",
"  	c None",
"..	c #3A32E4",
".+	c #FFFFFF",
"      ",
"......",
".+..  ",
"    .+",
"......"};

typedef struct  s_xpm
{
    int     ymax;
    int     xmax;
    int     colormax;
    int     nchar;
    int     *pixels;
}               t_xpm;

void    error()
{
    ft_putendl("erreur fichier ou malloc");
    //free tous les mallocs : xpm et xpm->pixels
    exit(0);
}

void    init_xpm(t_xpm *xpm, char *firstline)
{
    int i;

    xpm->ymax = ft_atoi(firstline);
    while (firstline[i] && firstline[i] != ' ')
        i++;
    while (firstline[i] == ' ') // pas besoin de verif c != '\0' car c == ' ' implique c != '\0'
        i++;
    xpm->xmax = ft_atoi(firstline + i);
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
    //printf("x = %d, y = %d, colors = %d, nchar = %d, \n", xpm->xmax, xpm->ymax, xpm->colormax, xpm->nchar);
    if (xpm->xmax < 1 || xpm->ymax < 1 || xpm->colormax < 1 || xpm->nchar < 1)
        error();
}

int     color_to_hex(char *colorline, int i)
// un exemple de colorline : xpm_file[2] = ".	c #3A32E4"
{
//i est sur le 1er bloc d'espaces, i = 1 ici
    while (colorline[i] == ' ' || colorline[i] == '\t')
        i++;
    while (colorline[i] && colorline[i] != ' ' && colorline[i] != '\t')
        i++;
    while (colorline[i] == ' ' || colorline[i] == '\t')
        i++;
//i est sur 3e et dernier mot, colorline + i = "#3A32E4" ici
    if (colorline[i] == '#')
        i++;
    return(strtol(colorline + i, NULL, 16));
}

int     get_hexpixel(t_xpm *xpm, char **xpm_file, int line, int i)
{
    int     i_color;
    char    **data;
    char    **tabcolor;

// l'image est stockee juste apres la derniere ligne des couleurs
    data = xpm_file + xpm->colormax + 1;
// les couleurs commencent a la 2nde ligne (xpm_file[1])
    tabcolor = xpm_file + 1;
    i_color = -1;
    while (++i_color < xpm->colormax)
    {
        if (!ft_strncmp(xpm_file[i_color + 1], data[line] + i * xpm->nchar, xpm->nchar))
            return (color_to_hex(xpm_file[i_color + 1], xpm->nchar));
    }
    return (-1);
}

t_xpm    get_xpm(char **xpm_file)
{
    int     line;
    int     i;
    t_xpm   xpm;

    init_xpm(&xpm, xpm_file[0]);
    if (!(xpm.pixels = (int *)ft_memalloc(sizeof(int) * xpm.xmax * xpm.ymax)))
        error();
    line = -1;
    while (++line < xpm.xmax)
    {
        i = -1;
        //ft_putnbr(line);
        //ft_putendl("");
        while (++i < xpm.ymax)
        {
            //ft_putstr("i = ");
            //ft_putnbr(i);
            //ft_putendl("");
            xpm.pixels[line * xpm.ymax + i] = get_hexpixel(&xpm, xpm_file, line, i);
            if (xpm.pixels[line * xpm.ymax + i] == -1)
                error();
        }
    }
    return(xpm);
}

void    print_pixeltab(t_xpm *xpm)
{
    int i;

    i = -1;
    while (++i < xpm->xmax * xpm->ymax)
    {
        ft_putnbr(xpm->pixels[i]);
        ft_putchar(' ');
        if ((i + 1) % xpm->ymax == 0)
            ft_putchar('\n');
    }

}

int     main()
{
    t_xpm   test_xpm;

    test_xpm = get_xpm(example2_xpm);
    print_pixeltab(&test_xpm);
    return (1);
}