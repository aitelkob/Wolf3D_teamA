/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:22:33 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/11 17:17:22 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void		inner_correction(int **map, int n, int m)
{
	int i;
	int j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < m)
		{
			if (map[i][j] == 0 && (i == 0 || j == 0))
			{
				ft_putstr("EROOR: Something wrong with the maps walls\n");
				free_map2(map, n);
				exit(1);
			}
			else if (map[i][j] == 0 && (i == 23 || j == 23))
			{
				ft_putstr("EROOR: Something wrong with the maps walls\n");
				free_map2(map, n);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void		correction(int **map, int n, int m)
{
	if (n != m)
	{
		free_map2(map, n);
		ft_putstr("EROOR: Map should be 24 x 24\n");
		exit(1);
	}
	inner_correction(map, n, m);
}

void		show_error2(char *str)
{
	ft_putstr("\033[1;31m                ERROR                    \033[0m\n");
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

int			**get_map(int **map, int fd, char **av)
{
	char	*line;
	char	**tab;
	int		n;
	int		i;
	int		m;

	m = line_numb(av[1]);
	if (m < 1)
		show_error2(av[1]);
	if (!(map = (int **)malloc(sizeof(int *) * (m + 1))))
		return (NULL);
	i = 0;
	while (get_next_line(fd, &line))
	{
		tab = ft_split_whitespaces(line);
		n = ft_strlen_2_dim(tab);
		n = check(n, i);
		map[i] = values(tab, n);
		free(line);
		free_map(tab, n);
		tab = NULL;
		i++;
	}
	correction(map, n, m);
	return (map);
}
