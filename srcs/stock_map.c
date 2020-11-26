/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:22:33 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/11/26 01:00:30 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void		show_error1()
{
    ft_putstr("\033[1;31m");
	ft_putstr(" : ヽ(｀⌒´メ)ノ There is no such map folder ヽ(｀⌒´メ)ノ");
    ft_putstr("\033[0m");
    ft_putchar('\n');
	exit(1);
}

void		show_error2(char *str)
{
    ft_putstr("\033[1;31m                    ERROR                    \033[0m\n");
    ft_putstr("                  ");
	ft_putstr(str);
    ft_putstr("\n\033[1;31m");
	ft_putstr("ヽ(｀⌒´メ)ノ  You can't fool me  ヽ(｀⌒´メ)ノ\n");
	ft_putstr("ヽ(｀⌒´メ)ノ   No  map is here   ヽ(｀⌒´メ)ノ\n");
	ft_putstr("ヽ(｀⌒´メ)ノ    File is empty    ヽ(｀⌒´メ)ノ");
    ft_putstr("\033[0m");
    ft_putchar('\n');
	exit(1);
}

void		show_error3()
{
    ft_putstr("\033[1;36m");
	ft_putstr("ヽ(｀⌒´メ)ノ Choose a Map from the maps folder ヽ(｀⌒´メ)ノ\n");
	ft_putstr("ヽ(｀⌒´メ)ノ   Try again using this sentence   ヽ(｀⌒´メ)ノ\n");
	ft_putstr("ヽ(｀⌒´メ)ノ   ./Wolf maps/[name-of-the-map]   ヽ(｀⌒´メ)ノ");
    ft_putstr("\033[0m");
    ft_putchar('\n');
	exit(1);
}

int			line_numb(char *argv)
{
	int		n;
	char	*line;
	int		fd;
	int		ret;

	n = 0;
	fd = open(argv, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		n++;
		free(line);
	}
	close(fd);
	return (n);
}

int			ft_strlen_2_dim(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

size_t		check(int n, int i)
{
	static int	nb;

	if (i == 0)
	{
		nb = n;
		return (n);
	}
	else if (n >= nb)
		return (nb);
	else
		return (n);
}

int		*values(char **tab, size_t len)
{
	size_t	i;
	int	*map;

	i = -1;
    if (!(map = (int*)malloc(sizeof(int) * (len + 1))))
		return (0);
	while (++i < len)
		map[i] = ft_atoi(tab[i]);
	return (map);
}

void        correction(int **map, int n, int m)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < m)
    {
        j = 0;
        while (j < m)
        {
            if (map[i][j] == 0 && (i == 0 || j == 0))
            {
                ft_putstr ("EROOR: Wall not detected\n");
                exit (1);
            }
            else if (map[i][j] == 0 && (i == n - 1 || j == m - 1))
            {
                printf("map[%d][%d] = %d", i+1, j+1, map[i][j]);
                write (1, "EROOR2\n", 7);
                exit (1);
            }
            j++;
        }
        i++;
    }
}

int         **get_map(int **map, int fd, char    **av)
{
    char    *line;
    char    **tab;
    int n;
    int i;
    int m;

    m = line_numb(av[1]);
	printf("%d",m);
    if (m < 1)
        show_error2(av[1]);
    if (!(map = (int**)malloc(sizeof(int*) * (m + 1))))
		return (NULL);

    i = 0;
    while (get_next_line(fd, &line))
    {
        tab = ft_split_whitespaces(line);
        n = ft_strlen_2_dim(tab);
        n = check(n, i);
        map[i] = values(tab, n);
        i++;
    }
    correction(map, n, m);
    return (map);
}
