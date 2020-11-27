/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:47:25 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/11/27 11:18:26 by ayagoumi         ###   ########.fr       */
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
/*
**	chi mochkil f had lfunction
*/
void        loadTexture(t_wolf_3d *w)
{
	w->sdl.cur = IMG_Load(PNG);
	w->sdl.wall = IMG_Load(MOSSY);
	w->sdl.wall2 = IMG_Load(WOOD);
	w->sdl.wall3 = IMG_Load(REDBRICK);
	w->sdl.wall4 = IMG_Load(GRAYSTONE);
	w->sdl.wall1 = IMG_Load(GRAYSTONE);
	w->sdl.wall_data_tmp = (unsigned int*)w->sdl.wall1->pixels;
	w->sdl.ceiling_texture = IMG_Load(REDBRICK);
	w->sdl.roof_texture = IMG_Load(PURPLESTONE);
	w->sdl.floor_texture = IMG_Load(MOSSY);
	w->sdl.wall_data_floor = (unsigned int*)w->sdl.floor_texture->pixels;
	// printf("this ceiling texture %d - wall4 = %d \n",w->sdl.ceiling_texture->w,w->sdl.wall4->w);
	/////// load texture
	
	w->sdl.cur_tex = SDL_CreateTextureFromSurface(w->sdl.renderer, w->sdl.cur);
}

void		texture_img(t_wolf_3d *w)
{
	loadTexture(w);
	SDL_UpdateTexture(w->sdl.texture, NULL, w->data, WIDTH * sizeof(int));
	SDL_RenderCopy(w->sdl.renderer, w->sdl.texture, NULL, NULL);
}
