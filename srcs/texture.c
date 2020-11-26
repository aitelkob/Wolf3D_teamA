/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:47:25 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/11/26 20:24:45 by ayagoumi         ###   ########.fr       */
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
	w->sdl.wall_data_tmp = (unsigned int*)w->sdl.wall4->pixels;
	w->sdl.ceiling_texture = IMG_Load(REDBRICK);
	w->sdl.roof_texture = IMG_Load(PURPLESTONE);
	w->sdl.floor_texture = IMG_Load(COLORSTONE);

	/////// load texture
	
	// w->sdl.wall = IMG_Load(MOSSY);
	// w->sdl.wall2 = IMG_Load(GRAYSTONE);
	// w->sdl.wall3 = IMG_Load(REDBRICK);
	// w->sdl.wall4 = IMG_Load(WOOD);
	// w->sdl.wall5 = IMG_Load(MOSSY);
	w->sdl.wall_data = malloc(sizeof(unsigned int) * 5);
	w->sdl.wall_h = malloc(sizeof(int) * 5);

	w->sdl.wall_data[0] = (unsigned int*)w->sdl.wall->pixels;
	w->sdl.wall_h[0] = w->sdl.wall->h;
	w->sdl.wall_data[1] = (unsigned int*)w->sdl.wall2->pixels;
	w->sdl.wall_h[1] = w->sdl.wall2->h;
	w->sdl.wall_data[2] = (unsigned int*)w->sdl.wall3->pixels;
	w->sdl.wall_h[2] = w->sdl.wall3->h;
	w->sdl.wall_data[3] = (unsigned int*)w->sdl.wall4->pixels;
	w->sdl.wall_h[3] = w->sdl.wall4->h;
	// w->sdl.wall_data[4] = (unsigned int*)w->sdl.wall5->pixels;
	// w->sdl.wall_h[4] = w->sdl.wall5->h;
	w->sdl.cur_tex = SDL_CreateTextureFromSurface(w->sdl.renderer, w->sdl.cur);
}

void		texture_img(t_wolf_3d *w)
{
	loadTexture(w);
	SDL_UpdateTexture(w->sdl.texture, NULL, w->data, WIDTH * sizeof(int));
	SDL_RenderCopy(w->sdl.renderer, w->sdl.texture, NULL, NULL);
}
