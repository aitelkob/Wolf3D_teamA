/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 10:27:01 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/10/27 11:17:40 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*void  draw_cube(t_wolf_3d *w, int x_begin, int y_begin, int color)
{
	int i;
	int j;

	j = x_begin;
	while (j < x_begin + CUBESIZE)
	{
		i = y_begin;
		while (i < y_begin + CUBESIZE)
		{
			w->data[i + (j * WIDTH)] = color;
			i++;
		}
		j++;
	}
}

void  draw_mini_cube(t_wolf_3d *w, int x_begin, int y_begin, int color)
{
	int i;
	int j;

	j = x_begin;
	while (j < x_begin + CUBESIZE)
	{
		i = y_begin;
		while (i < y_begin + CUBESIZE)
		{
			if (j != x_begin && j != x_begin + CUBESIZE - 1 && j && i != y_begin 
			&& i != y_begin + CUBESIZE - 1)
				w->data[i + (j * WIDTH)] = color;
			i++;
		}
		j++;
	}
}

void  draw_map(t_wolf_3d *w)
{
	int i;
	int j;

	i = 0;
	while (i < WIDTHMAP)
	{
		j = 0;
		while (j < HEIGTHMAP)
		{
			if (w->player.world_map[i / CUBESIZE][j / CUBESIZE] != 0)
				draw_cube(w, i, j, 0);
			else if ((int)(i / CUBESIZE) == (int)w->player.pos.x && (int)(j / CUBESIZE) == (int)w->player.pos.y)
				draw_cube(w, i, j, 0xff0000);
			else if (w->player.world_map[(int)(i / CUBESIZE)][(int)(j / CUBESIZE)] == 0)
				draw_cube(w, i, j, 0);
			j += CUBESIZE;
		}
		i += CUBESIZE;
	}
}*/