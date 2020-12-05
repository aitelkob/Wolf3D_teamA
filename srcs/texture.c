/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:47:25 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/04 23:49:53 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/wolf_3d.h"

void		image_clear(t_wolf_3d *wolf)
{
	int x;
	int j;

	x = 0;
	while (x < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			wolf->data[(WIDTH * j) + x] = 0;
			j++;
		}
		x++;
	}
}
