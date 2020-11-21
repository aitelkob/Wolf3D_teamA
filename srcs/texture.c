/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:47:25 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/11/20 10:56:26 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/wolf_3d.h"

/*SDL_Surface *loadMedia(char *path)
{
  SDL_Surface  *img;
  SDL_Surface  *tmp;

  tmp = IMG_Load(path);
  if (tmp == NULL)
    exit(1);
  img = tmp;

  SDL_FreeSurface(tmp);
  return (img);
}*/

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

void        loadTexture(t_wolf_3d *w)
{
	w->sdl.cur = IMG_Load(PNG);
	w->sdl.wall_wood = IMG_Load(WOOD);
	w->sdl.wall_data_wood = (unsigned int*)w->sdl.wall_wood->pixels;
	w->sdl.ceiling_texture = IMG_Load(REDBRICK);
	w->sdl.roof_texture = IMG_Load(PURPLESTONE);
	w->sdl.floor_texture = IMG_Load(COLORSTONE);

	/*int i = 0;
	unsigned int color_texture;
	while (i < TEXT_W)
	{
		printf("i= %d < TEXT_W = %d \n",i,TEXT_W);
		int y = 0;
		while (y < TEXT_H)
		{
			color_texture = w->sdl.wall_data_wood[(TEXT_W * y ) + i];
			w->data[(TEXT_W * y ) + i] = color_texture;
			y++;
		}
		i++;
	}*/
	w->sdl.cur_tex = SDL_CreateTextureFromSurface(w->sdl.renderer, w->sdl.cur);
}

void		texture_img(t_wolf_3d *w)
{
	loadTexture(w);
	SDL_UpdateTexture(w->sdl.texture, NULL, w->data, WIDTH * sizeof(int));
	SDL_RenderCopy(w->sdl.renderer, w->sdl.texture, NULL, NULL);
}
